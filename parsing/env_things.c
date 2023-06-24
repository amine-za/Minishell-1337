/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_things.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 23:47:09 by azaghlou          #+#    #+#             */
/*   Updated: 2023/06/24 12:07:39 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*env_chck(char *s, int indc, t_env *p)
{
	int		i;
	int		num_dllr;
	t_env	*head;
	char	*f_part;
	char	*var_name;

	i = -1;
	num_dllr = dollar_count(s);
	head = p;
	f_part = ft_calloc(1, ft_strlen(s) + 1);
	while (++i < indc && s[i])
		f_part[i] = s[i];
	var_name = variable_name(s, 0);
	f_part = search_for_var(p, var_name, f_part);
	while (num_dllr != 1)
	{
		p = head;
		free(var_name);
		var_name = variable_name(s, 0);
		f_part = search_for_var(p, var_name, f_part);
		num_dllr--;
	}
	f_part = ft_strjoin2(f_part, variable_name(s, 1));
	free(var_name);
	return (free(s), f_part);
}
