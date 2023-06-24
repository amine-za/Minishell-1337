/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation_things1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:59:44 by azaghlou          #+#    #+#             */
/*   Updated: 2023/06/24 20:32:38 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_append_or_herdoc(char *s, int *i, t_inf *p)
{
	if (s[i[0] + 1] && ((s[i[0]] == '<' && s[i[0] + 1] == '<' && p->in_dbl == 0
				&& p->in_sgl == 0) || (s[i[0]] == '>' && s[i[0] + 1] == '>'
				&& p->in_dbl == 0 && p->in_sgl == 0)))
		return (1);
	return (0);
}

int	if_pipe_or_red( char *s, int *i, t_inf *p)
{
	if ((s[i[0]] == '|' || s[i[0]] == '<' || s[i[0]] == '>') && p->in_dbl == 0
		&& p->in_sgl == 0)
		return (1);
	return (0);
}

char	**case_of_append_or_herdoc(char **ar, char *s, int *i)
{
	ar = chrjoin(ar, s[i[0]++], 1);
	ar = chrjoin(ar, s[i[0]++], 0);
	t_glbl_var_fct(1, 1);
	return (ar);
}
