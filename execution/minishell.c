/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:36:15 by nettalha          #+#    #+#             */
/*   Updated: 2023/06/24 15:01:11 by azaghlou         ###   ########.fr       */
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
			ft_error(cmd->cmd[0], strerror(errno), errno);
			exit(errno);
		}
	}
	else if (!valid_path && error == 2)
	{
		ft_error(cmd->cmd[0], "command not found", errno);
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

t_cmd	*parse(t_cmd *cmd, t_env *my_envp, char *line)
{
	cmd = parsing1(line, my_envp);
	if (!cmd || (!cmd->cmd[0] && !cmd->red))
	{
		free(line);
		return (NULL);
	}
	return (cmd);
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	*cmd;
	char	*line;
	t_env	*my_envp;

	save_fds(ac, av);
	my_envp = env_to_struct(envp);
	using_history();
	while (1)
	{
		ft_signals();
		line = readline("minishell$ ");
		if (!line)
			handle_exit(line);
		if (*line)
		{
			add_history(line);
			cmd = parse(cmd, my_envp, line);
			if (!cmd)
				continue ;
		}
		else
		{
			free(line);
			continue ;
		}
		if (cmd->rpipe == 0)
		{
			if (!exec_one_cmd(cmd, my_envp, line))
				continue ;
		}
		else
		{
			backup_fds();
			ft_pipe(cmd, &my_envp);
		}
		backup_free(cmd, line);
	}
	return (0);
}
