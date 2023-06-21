/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation_things.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:58:52 by azaghlou          #+#    #+#             */
/*   Updated: 2023/06/21 18:00:14 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**case_of_red_or_pipe(char **ar, char *s, int *i)
{
	ar = chrjoin(ar, s[i[0]++], 1);
	glbl_var_fct(0, 1);
	if (i[0] > 0 && s[i[0] - 1] != '|' && s[i[0] - 1] && s[i[0] + 1]
		&& !(s[i[0]] == '>' && s[i[0] - 1] == '<')
		&& !(s[i[0]] == '<' && s[i[0] - 1] == '>')
		&& !(s[i[0] - 1] == '>' && s[i[0]] == ' ' && s[i[0] + 1] == '<')
		&& !(s[i[0] - 1] == '<' && s[i[0]] == ' ' && s[i[0] + 1] == '>'))
		glbl_var_fct(1, 1);
	return (ar);
}

char	**case_of_sgl_quote(char **ar, char *s, int *i, t_inf *p)
{
	int	j;

	j = glbl_var_fct(0, 0);
	p->in_sgl = cls_or_opn_qt(p->in_sgl);
	if (p->in_sgl == 1 && i > 0 && s[i[0] - 1] == ' ')
		j = glbl_var_fct(1, 1);
	ar = chrjoin(ar, s[i[0]++], j);
	j = glbl_var_fct(0, 1);
	return (ar);
}

char	**case_of_dbl_quotes(char **ar, char *s, int *i, t_inf *p)
{
	int	j;

	j = glbl_var_fct(0, 0);
	p->in_dbl = cls_or_opn_qt(p->in_dbl);
	if (p->in_dbl == 1 && i > 0 && s[i[0] - 1] == ' ')
		j = glbl_var_fct(1, 1);
	ar = chrjoin(ar, s[i[0]++], j);
	j = glbl_var_fct(0, 1);
	return (ar);
}

void	case_of_space(int *i)
{
	glbl_var_fct(1, 1);
	i[0]++;
}

char	**els(char **ar, char *s, int *i)
{
	int	j;

	j = glbl_var_fct(0, 0);
	if (i[0] > 0 && s[i[0] - 1] == '|')
		j = glbl_var_fct(1, 1);
	ar = chrjoin(ar, s[i[0]++], j);
	j = glbl_var_fct(0, 1);
	return (ar);
}
