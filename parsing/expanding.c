/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:16:01 by azaghlou          #+#    #+#             */
/*   Updated: 2023/06/24 21:28:14 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*put_var_in(char *str, char *s, char *var)
{
	int	i;
	int	j;
	int	y;

	i = 0;
	j = 0;
	y = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			while (var[j])
				str[y++] = var[j++];
			while (s[i] && s[i] != ' ' && s[i] != '\"')
				i++;
			while (s[i])
				str[y++] = s[i++];
		}
		else
			str[y++] = s[i];
		i++;
	}
	str[y] = '\0';
	return (str);
}

char	*variable_name(char *s, int flag)
{
	static int	indc;
	char		*str;
	int			j;

	j = 0;
	if (flag == 1 && indc == 0)
		return ("\0");
	else if (flag == 1)
		return (&s[indc]);
	indc = point_in_dollar(s, indc);
	if (s[indc] == '$')
	{
		str = ft_calloc(1, ft_strlen(&s[indc++]) + 1);
		while (s[indc] && (ft_isalnum(s[indc])
				|| s[indc] == '_' || s[indc] == '?'))
			str[j++] = s[indc++];
		if (!s[indc])
			indc = 0;
		return (str);
	}
	return (NULL);
}

char	*search_for_var(t_env *p, char *var_name, char *f_part)
{
	char	*exit_stts;

	if (!var_name)
		return (f_part);
	if (var_name[0] == '?')
	{
		exit_stts = ft_itoa(g_glb.exit_status);
		f_part = ft_strjoin2(f_part, exit_stts);
		free(exit_stts);
		return (f_part);
	}
	while (p)
	{
		if (ft_strcmp(var_name, p->key) == 0)
			break ;
		p = p->next;
	}
	if (p == NULL)
		return (number_expen_case(f_part, var_name));
	f_part = ft_strjoin2(f_part, p->value);
	return (f_part);
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

char	**var_case(char **ar, t_env *env)
{
	int		j;
	int		i;
	t_inf	p;

	j = -1;
	i = -1;
	p.in_dbl = 0;
	p.in_sgl = 0;
	while (ar[++j])
	{
		while (ar[j][++i])
		{
			p = quotes_inf_for_var(p, ar[j], i);
			if (ar[j][i] == '$' && ar[j][i + 1] && p.in_sgl == 0
					&& (ft_isalnum(ar[j][i + 1])
					|| ar[j][i + 1] == '_' || ar[j][i + 1] == '?'))
			{
				ar[j] = env_chck(ar[j], i, env);
				i = -1;
				break ;
			}
		}
		i = -1;
	}
	return (ar);
}
