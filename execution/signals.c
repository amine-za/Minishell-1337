/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 21:50:35 by nettalha          #+#    #+#             */
/*   Updated: 2023/06/12 10:47:01 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <signal.h>

void handler(int num)
{
	if (num == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}

}

void	ft_signals(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}
