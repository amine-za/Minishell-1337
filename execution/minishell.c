/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:36:15 by nettalha          #+#    #+#             */
/*   Updated: 2023/06/24 21:37:49 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_glb	g_glb;

void	execute2(t_cmd	*cmd, t_env **my_envp)
{
	int		error;
	char	**envp;
	char	*valid_path;

	error = 0;
	valid_path = get_valid_path(cmd, *my_envp, &error);
	if (valid_path && !error)
	{
		envp = struct_to_env(my_envp);
		if (execve(valid_path, cmd->cmd, envp) == -1)
		{
			ft_error(cmd->cmd[0], "command not found", 127);
			exit(127);
		}
	}
	else if (!valid_path && error == 2)
	{
		ft_error(cmd->cmd[0], "command not found", 127);
		exit(127);
	}
}

int	execute(t_cmd	*cmd, t_env **my_envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		execute2(cmd, my_envp);
	return (pid);
}

int	exec_one_cmd(t_cmd *cmd, t_env *my_envp, char *line)
{
	pid_t	pid;

	if (!check_red(cmd, 0))
	{
		free(line);
		return (0);
	}
	if (cmd->cmd[0])
	{
		if (builtins(cmd, my_envp))
		{
			backup_free(cmd, line);
			return (0);
		}
		pid = execute(cmd, &my_envp);
		waitpid(pid, &g_glb.status, 0);
		g_glb.exit_status = WEXITSTATUS(g_glb.status);
	}
	return (1);
}

int	main_exc(char *line, t_cmd	*cmd, t_env	*my_envp)
{
	line = readline("minishell$ ");
	ft_exsignals();
	if (!line)
		handle_exit(line);
	if (*line)
	{
		add_history(line);
		cmd = parse(cmd, my_envp, line);
		if (!cmd)
			return (2);
	}
	else
		return (free(line), 2);
	if (cmd->rpipe == 0)
	{
		if (!exec_one_cmd(cmd, my_envp, line))
			return (2);
	}
	else
	{
		backup_fds();
		ft_pipe(cmd, &my_envp);
	}
	backup_free(cmd, line);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	*cmd;
	char	*line;
	t_env	*my_envp;

	my_envp = NULL;
	cmd = NULL;
	line = NULL;
	save_fds(ac, av);
	my_envp = env_to_struct(envp);
	using_history();
	while (1)
	{
		ft_signals();
		if (main_exc(line, cmd, my_envp) == 2)
			continue ;
	}
	return (0);
}
