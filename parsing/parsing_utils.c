/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:21:30 by azaghlou          #+#    #+#             */
/*   Updated: 2023/06/24 18:56:40 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*rm_quotes(char *s)
{
	int		i;
	int		j;
	t_inf	p;
	char	*str;

	i = -1;
	j = 0;
	p.in_sgl = 0;
	p.in_dbl = 0;
	str = ft_calloc(1, ft_strlen(s) + 1);
	while (s[++i])
	{
		if (s[i] == '\'' && p.in_dbl == 0)
			p.in_sgl = cls_or_opn_qt(p.in_sgl);
		else if (s[i] == '\"' && p.in_sgl == 0)
			p.in_dbl = cls_or_opn_qt(p.in_dbl);
		else
			str[j++] = s[i];
	}
	return (str);
}

int	count_pipes(char *s)
{
	int		i;
	int		res;
	t_inf	p;

	i = 0;
	res = 0;
	p.in_sgl = 0;
	p.in_dbl = 0;
	while (s[i])
	{
		if (s[i] == '\'' && p.in_dbl == 0)
			p.in_sgl = cls_or_opn_qt(p.in_sgl);
		else if (s[i] == '\"' && p.in_sgl == 0)
			p.in_dbl = cls_or_opn_qt(p.in_dbl);
		else if (s[i] == '|' && p.in_dbl == 0 && p.in_sgl == 0)
			res++;
		i++;
	}
	return (res);
}
