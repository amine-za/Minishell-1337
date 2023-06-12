/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:36:15 by nettalha          #+#    #+#             */
/*   Updated: 2023/06/12 23:50:54 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_cmd(t_cmd *cmd)
{
	int i = 0;
	while(cmd->cmd[i])
		printf("cmd: %s\n", cmd->cmd[i++]);
	i = 0;
	while(cmd->red[i])
		printf("red: %s\n", cmd->red[i++]);
	i = 0;
	while(cmd->file[i])
		printf("file: %s\n", cmd->file[i++]);
	i = 0;
	while(cmd->delimiter[i])
		printf("delimiter: %s\n", cmd->delimiter[i++]);
}

int	execute(t_cmd	*cmd, t_env **my_envp)
{
	pid_t	pid;
	int		error;
	char	**envp;
	char	*valid_path;
	// printf("hello from execute function\n");
	error = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		// if (cmd->red)
		// {
		// 	if (cmd->delimiter)
		// 	{
		// 		printf("herdoc from execute\n");
		// 		ft_herdoc(cmd);
		// 	}
		// 	if (cmd->file)
		// 		redirect(cmd);
		// }
		valid_path = get_valid_path(cmd, *my_envp, &error);
		if (valid_path && !error)
		{
			envp = struct_to_env(my_envp);
			if (execve(valid_path, cmd->cmd, envp) == -1)
			{
				printf("minishell: %s: %s\n", cmd->cmd[0], strerror(errno));
				ft_free(cmd->cmd);
				//free(line);
				printf(">>>>66\n");
				global.exit_status = 127;
				exit(global.exit_status);
			}
		}
		else if (!valid_path && error == 2)
		{
			printf("hello\n");
			printf("minishell: %s: command not found\n", cmd->cmd[0]);
			printf(">>>>75\n");
			global.exit_status = 127;
			exit(127);
		}
	}
	return (pid);
}

char	*get_valid_path(t_cmd	*cmd, t_env *env, int *error)
{
	char	*valid_path;

	valid_path = NULL;
	if (!cmd->cmd[0])
		return(NULL);
	if (ft_strchr(cmd->cmd[0], '/') != NULL && !access(cmd->cmd[0], F_OK | R_OK | X_OK))
		valid_path = ft_strdup(cmd->cmd[0]);
	else if (ft_strnstr(cmd->cmd[0], "./", ft_strlen(cmd->cmd[0])))
	{
		if (!access(cmd->cmd[0], F_OK | R_OK | X_OK))
			valid_path = ft_strdup(cmd->cmd[0]);
		else
			ft_error(cmd->cmd[0], strerror(errno), errno);
	}
	else
	{
		valid_path = getpath(cmd->cmd[0], env, error);
	}
	return (valid_path);
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	*cmd;
	char	*line;
	t_env	*my_envp;
	pid_t	pid;
	int		original_stdin;
	int		original_stdout;


	(void)ac;
	(void)av;
	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	my_envp = env_to_struct(envp);
	using_history();
	while (1)
	{
		ft_signals();
		line = readline("\033[1;35mminishell$ \033[0m");
		if (!line)
			exit (global.exit_status);
		if (*line)
		{
			add_history(line);
			cmd = parsing1(line, my_envp);
			if (!cmd || (!cmd->cmd[0] && !cmd->red))
				continue ;
		}
		else
			continue ;
		if (cmd->red)
		{
			if (cmd->delimiter)
			{
				// printf("herdoc from pipes\n");
				ft_herdoc(cmd);
			}
			if (cmd->file)
				redirect(cmd);
		}
		if (cmd->Rpipe == 0)
		{
			if (builtins(cmd, my_envp))
			{
				// if (cmd->cmd && cmd->delimiter)
				// {
				// 	printf("herdoc from builtins\n");
				// 	ft_herdoc(cmd);
				// }
				dup2(original_stdin, STDIN_FILENO);
				dup2(original_stdout, STDOUT_FILENO);
				continue;
			}
			pid = execute(cmd, &my_envp);
			waitpid(pid, NULL, 0);
		}
		else
		{
			ft_pipe(cmd, &my_envp);
		}
		dup2(original_stdin, STDIN_FILENO);
		dup2(original_stdout, STDOUT_FILENO);
		ft_free(cmd->cmd);
		free(cmd);
		free(line);
		// pause();
		// unlink(cmd->heredoc_file);
	}
	return (0);
}
