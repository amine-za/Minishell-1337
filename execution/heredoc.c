/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:38:37 by nettalha          #+#    #+#             */
/*   Updated: 2023/06/24 17:37:48 by nettalha         ###   ########.fr       */
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
}

int	is_equal(char *delimiter, char *line)
{
	if (!line || !ft_strcmp(delimiter, line) || g_glb.sigint == 1)
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
		herdoc_signals();
		line = readline("> ");
		if (is_equal(cmd->delimiter[i], line))
			break ;
		write_in_file(cmd, line, i);
		free(line);
	}
	if (cmd->delimiter[i + 1] == NULL)
	{
		cmd->fd1 = open(heredoc_file, O_RDONLY, 0777);
		dup2(cmd->fd1, STDIN_FILENO);
		free(heredoc_file);
		close (cmd->fd1);
	}
}

void	heredoc1(t_cmd *cmd, int i)
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
		herdoc_signals();
		line = readline("> ");
		if (is_equal(cmd->delimiter[i], line))
			break ;
		write_in_file(cmd, line, i);
		free(line);
	}
	if (cmd->delimiter[i + 1] == NULL)
	{
		cmd->fd1 = open(heredoc_file, O_RDONLY, 0777);
		dup2(STDIN_FILENO, cmd->fd1);
		free(heredoc_file);
		close (cmd->fd1);
	}
}

void	ft_herdoc(t_cmd *cmd, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	g_glb.sigint = 0;
	while (cmd->red[i])
	{
		if (!ft_strcmp("<<", cmd->red[i]) && n == 0)
			heredoc(cmd, j++);
		i++;
	}
}
