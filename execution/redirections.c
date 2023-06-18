/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:55:28 by nettalha          #+#    #+#             */
/*   Updated: 2023/06/18 22:42:07 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirect(t_cmd	*cmd)
{
	int	i;

	i = 0;
	while (cmd->red[i])
	{
		if (!ft_strcmp(cmd->red[i], ">>"))
		{
			cmd->fd0 = open(cmd->file[i], O_RDWR | O_CREAT | O_APPEND, 0777);
			if (cmd->fd0 == -1)
			{
				ft_error(cmd->file[i], "ambiguous redirect", 126);
				dup2(g_glb.o_stdin, STDIN_FILENO);
				dup2(g_glb.o_stdout, STDOUT_FILENO);
				return (-1);
			}
			dup2(cmd->fd0, STDOUT_FILENO);
		}
		else if (!ft_strcmp(cmd->red[i], ">"))
		{
			cmd->fd0 = open(cmd->file[i], O_RDWR | O_TRUNC | O_CREAT, 0777);
			if (cmd->fd0 == -1)
			{
				ft_error(cmd->file[i], "ambiguous redirect", 126);
				dup2(g_glb.o_stdin, STDIN_FILENO);
				dup2(g_glb.o_stdout, STDOUT_FILENO);
				return (-1);
			}
			dup2(cmd->fd0, STDOUT_FILENO);
		}
		else if (!ft_strcmp(cmd->red[i], "<"))
		{
			cmd->fd0 = open(cmd->file[i], O_RDONLY, 0777);
			if (cmd->fd0 == -1)
			{
				ft_error(cmd->file[i], strerror(errno), 126);
				dup2(g_glb.o_stdin, STDIN_FILENO);
				dup2(g_glb.o_stdout, STDOUT_FILENO);
				return (-1);
			}
			dup2(cmd->fd0, STDIN_FILENO);
		}
		i++;
	}
	close(cmd->fd0);
	return (0);
}
