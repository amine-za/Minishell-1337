/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:55:28 by nettalha          #+#    #+#             */
/*   Updated: 2023/06/23 17:29:04 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_red(t_cmd *cmd, int n)
{
	if (cmd->red)
	{
		printf("entred0\n");
		if (cmd->delimiter && n == 0)
			ft_herdoc(cmd, 0);
		else if (cmd->delimiter && n == 1)
		{
			printf("entred1\n");
			ft_herdoc(cmd, 1);
		}
		if (cmd->file)
		{
			if (redirect(cmd) == -1)
				return (0);
		}
	}
	return (1);
}

int	dup_append(t_cmd *cmd, int i)
{
	cmd->fd0 = open(cmd->file[i], O_RDWR | O_CREAT | O_APPEND, 0777);
	if (cmd->fd0 == -1)
	{
		ft_error(cmd->file[i], "ambiguous redirect", 126);
		dup2(g_glb.o_stdin, STDIN_FILENO);
		dup2(g_glb.o_stdout, STDOUT_FILENO);
		return (0);
	}
	dup2(cmd->fd0, STDOUT_FILENO);
	return (1);
}

int	dup_out(t_cmd *cmd, int i)
{
	cmd->fd0 = open(cmd->file[i], O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (cmd->fd0 == -1)
	{
		ft_error(cmd->file[i], "ambiguous redirect", 126);
		dup2(g_glb.o_stdin, STDIN_FILENO);
		dup2(g_glb.o_stdout, STDOUT_FILENO);
		return (0);
	}
	dup2(cmd->fd0, STDOUT_FILENO);
	return (1);
}

int	dup_in(t_cmd *cmd, int i)
{
	cmd->fd0 = open(cmd->file[i], O_RDONLY, 0777);
	if (cmd->fd0 == -1)
	{
		ft_error(cmd->file[i], strerror(errno), 126);
		dup2(g_glb.o_stdin, STDIN_FILENO);
		dup2(g_glb.o_stdout, STDOUT_FILENO);
		return (0);
	}
	dup2(cmd->fd0, STDIN_FILENO);
	return (1);
}

int	redirect(t_cmd	*cmd)
{
	int	i;

	i = 0;
	while (cmd->red[i])
	{
		if (!ft_strcmp(cmd->red[i], ">>"))
		{
			if (!dup_append(cmd, i))
				return (-1);
		}
		else if (!ft_strcmp(cmd->red[i], ">"))
		{
			if (!dup_out(cmd, i))
				return (-1);
		}
		else if (!ft_strcmp(cmd->red[i], "<"))
		{
			if (!dup_in(cmd, i))
				return (-1);
		}
		i++;
	}
	return (0);
}
