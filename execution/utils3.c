/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 23:48:26 by nettalha          #+#    #+#             */
/*   Updated: 2023/06/24 10:51:44 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	backup_free(t_cmd *cmd, char *line)
{
	backup_fds();
	free(line);
	free_ll(cmd);
}
void	save_fds(int ac , char **av)
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