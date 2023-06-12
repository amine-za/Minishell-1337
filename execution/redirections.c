/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:55:28 by nettalha          #+#    #+#             */
/*   Updated: 2023/06/06 18:57:27 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirect(t_cmd	*cmd)
{
	int	i;

	i = 0;
	while (cmd->red[i])
	{
		// printf("----------welcome to my amazing redirection function %d----------\n", i);
		if (!ft_strcmp(cmd->red[i], ">>"))
		{
			cmd->fd0 = open(cmd->file[i], O_RDWR | O_CREAT | O_APPEND, 0777);
			dup2(cmd->fd0, STDOUT_FILENO);
		}
		else if (!ft_strcmp(cmd->red[i], ">"))
		{
			cmd->fd0 = open(cmd->file[i], O_RDWR | O_TRUNC | O_CREAT, 0777);
			dup2(cmd->fd0, STDOUT_FILENO);
		}
		else if (!ft_strcmp(cmd->red[i], "<"))
		{
			cmd->fd0 = open(cmd->file[i], O_RDONLY, 0777);
			if (cmd->fd0 == -1)
			{
				printf("minishell: %s: %s\n", cmd->file[i], strerror(errno));
				i++;
				continue;
			}
			dup2(cmd->fd0, STDIN_FILENO);
		}
		i++;
	}
	close(cmd->fd0);
	close(cmd->fd1);
	return (0);
}
