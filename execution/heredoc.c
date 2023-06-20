/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:38:37 by nettalha          #+#    #+#             */
/*   Updated: 2023/06/20 23:30:43 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_in_file(t_cmd *cmd, char *line, int i)
{
	if (cmd->delimiter[i + 1] == NULL)
	{
		write(cmd->fd1, line, ft_strlen(line));
		write(cmd->fd1, "\n", 1);
	}
	free(line);
}

int	is_equal(char *delimiter, char *line)
{
	if (!ft_strcmp(delimiter, line))
	{
		free(line);
		return (1);
	}
	return (0);
}

void	heredoc(t_cmd *cmd, int i)
{
	char	*line;
	char	*heredoc_file;

	if (cmd->delimiter[i + 1] == NULL)
	{
		heredoc_file = ft_strjoin("/tmp/", cmd->delimiter[i]);
		cmd->fd1 = open((char *)heredoc_file, O_RDWR | O_TRUNC | O_CREAT, 0777);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || is_equal(cmd->delimiter[i], line))
			break ;
		write_in_file(cmd, line, i);
	}
	if (cmd->delimiter[i + 1] == NULL && cmd->Lpipe == 1 && cmd->Rpipe == 0)
	{
		cmd->fd1 = open(heredoc_file, O_RDONLY, 0777);
		dup2(cmd->fd1, STDIN_FILENO);
	}
}

void	ft_herdoc(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd->red[i])
	{
		if (!ft_strcmp("<<", cmd->red[i]))
			heredoc(cmd, j++);
		i++;
	}
}
