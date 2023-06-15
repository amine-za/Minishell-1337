/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:38:37 by nettalha          #+#    #+#             */
/*   Updated: 2023/06/15 11:57:26 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc(t_cmd *cmd, int i)
{
	char	*line;

	if (cmd->delimiter[i + 1] == NULL)
	{
		cmd->heredoc_file = ft_strjoin("/tmp/", cmd->delimiter[i]);
		cmd->fd1 = open((char *)cmd->heredoc_file, O_RDWR | O_TRUNC | O_CREAT, 0777);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(cmd->delimiter[i], line))
		{
			free(line);
			break ;
		}
		if (cmd->delimiter[i + 1] == NULL)
		{
			write(cmd->fd1, line, ft_strlen(line));
			write(cmd->fd1, "\n", 1);
		}
		free(line);
	}
	if (cmd->delimiter[i + 1] == NULL)
	{
		cmd->fd1 = open(cmd->heredoc_file, O_RDONLY, 0777);
		dup2(cmd->fd1, STDIN_FILENO);
	}
}

void	ft_herdoc(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(cmd->red[i])
	{
		if (!ft_strcmp("<<", cmd->red[i]))
			heredoc(cmd, j++);
		i++;
	}
}
