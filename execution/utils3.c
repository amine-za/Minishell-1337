/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 23:48:26 by nettalha          #+#    #+#             */
/*   Updated: 2023/06/24 18:10:41 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*parse(t_cmd *cmd, t_env *my_envp, char *line)
{
	cmd = parsing1(line, my_envp);
	if (!cmd || (!cmd->cmd[0] && !cmd->red))
	{
		free(line);
		return (NULL);
	}
	return (cmd);
}

void	backup_free(t_cmd *cmd, char *line)
{
	backup_fds();
	free(line);
	free_ll(cmd);
}

void	save_fds(int ac, char **av)
{
	(void)ac;
	(void)av;
	g_glb.o_stdin = dup(STDIN_FILENO);
	g_glb.o_stdout = dup(STDOUT_FILENO);
}

void	handle_exit(char *line)
{
	free(line);
	exit(g_glb.exit_status);
}

void	check_herdoc(t_cmd *cmd)
{
	t_cmd	*current;
	int		i;

	i = 0;
	current = cmd;
	while (current)
	{
		if (current->red[0] && current->delimiter)
		{
			while (current->delimiter[i])
			{
				heredoc1(current, i);
				i++;
			}
			i = 0;
		}
		current = current->next;
	}
}
