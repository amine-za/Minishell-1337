/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:18:53 by nettalha          #+#    #+#             */
/*   Updated: 2023/06/20 11:35:36 by nettalha         ###   ########.fr       */
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

void	pipes_exec(t_cmd	*cmd, t_env **my_envp)
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
			printf("minishell: %s: %s\n", cmd->cmd[0], strerror(errno));
			ft_free(cmd->cmd);
			exit(errno);
		}
	}
	else if (!valid_path && error == 2)
	{
		printf("minishell: %s: %s\n", cmd->cmd[0], strerror(errno));
		exit(127);
	}
}

void	ft_pipe(t_cmd *cmd, t_env **my_envp)
{
	int		**fd;
	pid_t	*pid;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = ft_cmdsize(cmd) - 1;
	fd = malloc(sizeof(int *) * (size + 1));
	pid = malloc(sizeof(pid_t) * (size + 1));
	while (i <= size)
		fd[i++] = malloc(sizeof(int) * 2);
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
	i = 0;
	while (i <= size && cmd)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			perror("fork");
			return ;
		}
		else if (pid[i] == 0)
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
			j = 0;
			while (j <= size)
			{
				close(fd[j][0]);
				close(fd[j][1]);
				j++;
			}
			if (cmd->red)
			{
				printf("i'm here\n");
				if (cmd->delimiter)
					ft_herdoc(cmd);
				if (cmd->file)
					redirect(cmd);
			}
			if (!builtins(cmd, *my_envp))
				pipes_exec(cmd, my_envp);
			else
				exit(EXIT_SUCCESS);
		}
		cmd = cmd->next;
		i++;
	}
	i = 0;
	while (i <= size)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	i = 0;
	while (i <= size)
	{
		waitpid(pid[i], &g_glb.status, 0);
		g_glb.exit_status = WEXITSTATUS(g_glb.status);
		i++;
	}
	i = 0;
	while (i <= size)
		free(fd[i++]);
	free(fd);
}
