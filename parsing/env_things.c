/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_things.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 23:47:09 by azaghlou          #+#    #+#             */
/*   Updated: 2023/06/22 20:01:34 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	var_name = variable_name(s);
	f_part = search_for_var(p, var_name, f_part);
	while (num_dllr != 1)
	{
		p = head;
		free(var_name);
		var_name = variable_name(s);
		f_part = search_for_var(p, var_name, f_part);
		num_dllr--;
	}
	free(s);
	free(var_name);
	return (f_part);
}
