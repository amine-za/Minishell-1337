/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:03:28 by nettalha          #+#    #+#             */
/*   Updated: 2023/06/23 16:04:30 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_fds(int **fd, int i, int size)
{
	if (i == 0)
		dup2(fd[i][1], STDOUT_FILENO);
	else if (i == size)
		dup2(fd[i - 1][0], STDIN_FILENO);
	else
	{
		dup2(fd[i][1], STDOUT_FILENO);
		dup2(fd[i - 1][0], STDIN_FILENO);
	}
}

void	alloc_fds(int **fd, int size)
{
	int	i;

	i = 0;
	while (i <= size)
		fd[i++] = malloc(sizeof(int) * 2);
}

void	fds_opertions(int **fd, pid_t	*pid, int size, int n)
{
	(void)pid;
	if (n == 1)
	{
		alloc_fds(fd, size);
		pipe_fds(fd, size);
	}
	else if (n == 2)
	{
		close_fds(fd, size);
		wait_pids(pid, size);
		free(pid);
		free_fds(fd, size);
	}
}
