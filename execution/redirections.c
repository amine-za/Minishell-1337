/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:55:28 by nettalha          #+#    #+#             */
/*   Updated: 2023/06/21 17:05:33 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_red(t_cmd *cmd)
{
	if (cmd->red)
	{
		if (cmd->delimiter)
			ft_herdoc(cmd);
		if (cmd->file)
		{
			if (redirect(cmd) == -1)
			{
				return (0);
			}
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
	close(cmd->fd0);
	return (0);
}
