/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_things.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 23:47:09 by azaghlou          #+#    #+#             */
/*   Updated: 2023/06/24 15:14:33 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	point_in_dollar(char *s, int indc)
{
	while (s[indc])
	{
		if (s[indc] == '$' && s[indc + 1] && (ft_isalnum(s[indc + 1])
				|| s[indc + 1] == '_' || s[indc + 1] == '?'))
			break ;
		indc++;
	}
	return (indc);
}

t_inf	quotes_inf_for_var(t_inf p, char *ar, int i)
{
	if (ar[i] && ar[i] == '\'')
		p.in_sgl = cls_or_opn_qt(p.in_sgl);
	if (ar[i] && ar[i] == '\"')
		p.in_dbl = cls_or_opn_qt(p.in_dbl);
	return (p);
}

int	dollar_count(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] && (ft_isalnum(s[i + 1]) || s[i + 1] == '_'
				|| s[i + 1] == '?'))
			count++;
		i++;
	}
	return (count);
}

void	env_chck_norm(char *f_part, char *s, int i, int indc)
{
	while (i < indc && s[i])
	{
		f_part[i] = s[i];
		i++;
	}
}

char	*number_expen_case(char *f_part, char *var_name)
{
	int	i;

	i = 0;
	if (ft_isdigit(var_name[0]))
		return (ft_strjoin2(f_part, &var_name[1]));
	return (f_part);
}
