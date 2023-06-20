/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 22:57:56 by azaghlou          #+#    #+#             */
/*   Updated: 2023/06/20 15:54:53 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_redirec(char *s)
{
	if (!ft_strcmp(s, ">>"))
		return (1);
	if (!ft_strcmp(s, "<<"))
		return (1);
	if (!ft_strcmp(s, ">"))
		return (1);
	if (!ft_strcmp(s, "<"))
		return (1);
	return (0);
}

int	redirection_err(char **ar)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	while (ar[i])
	{
		if (if_redirec(ar[i]) && !ar[i + 1])
			err = 1;
		if (i > 0 && if_redirec(ar[i]) == 1 && if_redirec(ar[i - 1]))
			err = 1;
		if (ar[i + 1] && if_redirec(ar[i]) && ar[i + 1][0] == '|')
			err = 1;
		i++;
	}
	if (err == 1)
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		g_glb.exit_status = 258;
		return (1);
	}
	return (0);
}

int	pipes_err(char **ar)
{
	int	i;
	int	err;

	i = 1;
	err = 0;
	if (!ar[0])
		return (0);
	if (ar[0][0] == '|')
		err = 1;
	while (ar[i])
	{
		if (ar[i][0] == '|' && ar[i - 1][0] == '|')
			err = 1;
		i++;
	}
	if (ar[i - 1][0] == '|')
		err = 1;
	if (err == 1)
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		g_glb.exit_status = 258;
		return (1);
	}
	return (0);
}

int	quotes_err(char **ar)
{
	int	i;

	i = 0;
	while (ar[i])
	{
		if (rm_quotes(ar[i], 1) == NULL)
		{
			ft_putstr_fd("minishell: syntax error\n", 2);
			g_glb.exit_status = 258;
			return (1);
		}
		i++;
	}
	return (0);
}

int	syntaxe_err(char **ar)
{
	if (pipes_err(ar) == 1)
		return (1);
	if (redirection_err(ar) == 1)
		return (1);
	if (quotes_err(ar) == 1)
		return (1);
	return (0);
}
