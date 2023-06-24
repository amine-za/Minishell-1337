/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 21:50:35 by nettalha          #+#    #+#             */
/*   Updated: 2023/06/24 15:00:08 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <signal.h>

void	handler(int num)
{
	if (num == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	interrupt_heredoc(int num)
{
	if (num == SIGINT)
	{
		g_glb.exit_status = 1;
		g_glb.sigint = 1;
	}
}

void	ft_signals(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

void	herdoc_signals(void)
{
	signal(SIGINT, interrupt_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
