/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:18:53 by nettalha          #+#    #+#             */
/*   Updated: 2023/06/23 16:50:53 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipes_exec(t_cmd *cmd, t_env **my_envp)
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
			ft_free(cmd->cmd);
			g_glb.exit_status = errno;
			exit(errno);
		}
	}
	else if (!valid_path && error == 2)
	{
		ft_error(cmd->cmd[0], strerror(errno), errno);
		g_glb.exit_status = 127;
		exit(127);
	}
}

int	ft_pipe2(t_cmd *cmd, t_env **my_envp, pid_t *pid, int **fd)
{
	int	i;
	int	size;

	i = -1;
	size = ft_cmdsize(cmd) - 1;
	while (++i <= size && cmd)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			return (perror("fork"), 0);
		else if (pid[i] == 0)
		{
			dup_fds(fd, i, size);
			close_fds(fd, size);
			if (!check_red(cmd))
				continue ;
			if (!builtins(cmd, *my_envp))
				pipes_exec(cmd, my_envp);
			exit(EXIT_SUCCESS);
		}
		cmd = cmd->next;
	}
	return (1);
}

void	ft_pipe(t_cmd *cmd, t_env **my_envp)
{
	int		**fd;
	pid_t	*pid;
	int		size;
	int		i;

	size = ft_cmdsize(cmd) - 1;
	fd = malloc(sizeof(int *) * (size + 1));
	pid = malloc(sizeof(pid_t) * (size + 1));
	fds_opertions(fd, pid, size, 1);
	i = -1;
	if (!ft_pipe2(cmd, my_envp, pid, fd))
		return ;
	fds_opertions(fd, pid, size, 2);
}
