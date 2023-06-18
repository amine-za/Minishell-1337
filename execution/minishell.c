/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:36:15 by nettalha          #+#    #+#             */
/*   Updated: 2023/06/18 13:39:45 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

glb	g_glb;

void	print_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[i])
		printf("cmd: %s\n", cmd->cmd[i++]);
	i = 0;
	while (cmd->red[i])
		printf("red: %s\n", cmd->red[i++]);
	i = 0;
	while (cmd->file[i])
		printf("file: %s\n", cmd->file[i++]);
	i = 0;
	while (cmd->delimiter[i])
		printf("delimiter: %s\n", cmd->delimiter[i++]);
}

int	execute(t_cmd	*cmd, t_env **my_envp)
{
	pid_t	pid;
	int		error;
	char	**envp;
	char	*valid_path;

	error = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		valid_path = get_valid_path(cmd, *my_envp, &error);
		if (valid_path && !error)
		{
			envp = struct_to_env(my_envp);
			if (execve(valid_path, cmd->cmd, envp) == -1)
			{
				printf("minishell: %s: %s\n", cmd->cmd[0], strerror(errno));
				ft_free(cmd->cmd);
				printf("errno>> %d\n", errno);
				exit(errno);
			}
		}
		else if (!valid_path && error == 2)
		{
			printf("minishell: %s: command not found\n", cmd->cmd[0]);
			exit(127);
		}
	}
	return (pid);
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	*cmd;
	char	*line;
	t_env	*my_envp;
	pid_t	pid;

	(void)ac;
	(void)av;
	g_glb.o_stdin = dup(STDIN_FILENO);
	g_glb.o_stdout = dup(STDOUT_FILENO);
	my_envp = env_to_struct(envp);
	using_history();
	while (1)
	{
		ft_signals();
		line = readline("\033[1;35mminishell$ \033[0m");
		if (!line)
			exit (g_glb.exit_status);
		if (*line)
		{
			add_history(line);
			cmd = parsing1(line, my_envp);
			if (!cmd || (!cmd->cmd[0] && !cmd->red))
			{
				continue ;
			}
		}
		else
		{
			continue ;
		}
		if (cmd->red)
		{
			if (cmd->delimiter)
				ft_herdoc(cmd);
			if (cmd->file)
			{
				if (redirect(cmd) == -1)
				{
					continue ;
				}
			}
		}
		if (cmd->Rpipe == 0)
		{
			if (builtins(cmd, my_envp))
			{
				dup2(g_glb.o_stdin, STDIN_FILENO);
				dup2(g_glb.o_stdout, STDOUT_FILENO);
				continue ;
			}
			pid = execute(cmd, &my_envp);
			waitpid(pid, &g_glb.status, 0);
			g_glb.exit_status = WEXITSTATUS(g_glb.status);
			printf("main_exit_status>> %d\n", g_glb.exit_status);
		}
		else
		{
			dup2(g_glb.o_stdin, STDIN_FILENO);
			dup2(g_glb.o_stdout, STDOUT_FILENO);
			ft_pipe(cmd, &my_envp);
		}
		dup2(g_glb.o_stdin, STDIN_FILENO);
		dup2(g_glb.o_stdout, STDOUT_FILENO);
		ft_free(cmd->cmd);
		free(cmd);
		free(line);
	}
	return (0);
}
