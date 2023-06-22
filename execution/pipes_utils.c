/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:14:02 by nettalha          #+#    #+#             */
/*   Updated: 2023/06/22 12:51:38 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cmdsize(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd != NULL)
	{
		cmd = cmd->next;
		i++;
	}
	return (i);
}

void	pipe_fds(int **fd, int size)
{
	int	i;

	i = 0;
	while (i <= size)
	{
		if (pipe(fd[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	 close_fds(int **fd, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (close (fd[i][0]) == -1 || close (fd[i][1]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	wait_pids(pid_t	*pid, int size)
{
	int	i;

	i = 0;
	// printf("size>>|%d|\n", size);
	while (i <= size)
	{
		waitpid(pid[i], &g_glb.status, 0);
		g_glb.exit_status = WEXITSTATUS(g_glb.status);
		i++;
	}
}

void	free_fds(int **fd, int size)
{
	int	i;

	i = 0;
	while (i <= size)
		free(fd[i++]);
	free(fd);
}
