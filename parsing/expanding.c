/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:16:01 by azaghlou          #+#    #+#             */
/*   Updated: 2023/06/18 20:10:40 by azaghlou         ###   ########.fr       */
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

int	var_name_norm(char *s, int indc)
{
	while (s[indc])
	{
		if (s[indc] == '$' && s[indc + 1] && (ft_isalpha(s[indc + 1])
				|| s[indc + 1] == '_' || s[indc + 1] == '?'))
			break ;
		indc++;
	}
	return (indc);
}

char	*variable_name(char *s)
{
	static int	indc;
	char		*str;
	int			i;
	int			j;

	i = 0;
	j = 0;
	indc = var_name_norm(s, indc);
	i = indc;
	if (s[i] == '$')
	{
		str = ft_calloc(1, ft_strlen(&s[i++]) + 1);
		while (s[i] && (ft_isalnum(s[i]) || s[i] == '_' || s[i] == '?'))
			str[j++] = s[i++];
		if (!s[i])
			indc = 0;
		else
			indc = i;
		return (str);
	}
	if (!s[i])
		indc = 0;
	if (s[indc] == '$')
		indc++;
	return (NULL);
}

char	*search_for_var(t_env *p, char *var_name, char *f_part)
{
	if (!var_name)
		return (f_part);
	if (var_name[0] == '?')
	{
		f_part = ft_strjoin(f_part, ft_itoa(g_glb.exit_status));
		return (f_part);
	}
	while (p->next)
	{
		if (ft_strcmp(var_name, p->key) == 0)
			break ;
		p = p->next;
		if (p->next == NULL)
			return (f_part);
	}
	f_part = ft_strjoin(f_part, p->value);
	return (f_part);
}

char	**var_case(char **ar, t_env *env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ar[j])
	{
		while (ar[j][i] && ar[j][0] != '\'')
		{
			if (ar[j][i] == '$' && ar[j][i + 1] && (ft_isalnum(ar[j][i + 1])
					|| ar[j][i + 1] == '_' || ar[j][i + 1] == '?'))
			{
				ar[j] = env_chck(ar[j], i, env);
				break ;
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (ar);
}
// char	*check_num_case(char *first_part, char *s, int sttc)
// {
// 	char	*str;

// 	while (s[sttc])
// 	{
// 		if (s[sttc] == '$' && s[sttc + 1] && (ft_isdigit(s[sttc + 1])
// 				|| s[sttc + 1] == '_'))
// 			break ;
// 		sttc++;
// 	}
// 	if (ft_isdigit(s[sttc + 1]))
// 	{
// 		if (s[sttc + 2])
// 			str = &s[sttc + 2];
// 		else
// 			return (first_part);
// 		sttc += 2;
// 		while (str[sttc] && str[sttc] != '$')
// 			sttc++;
// 		str[sttc] = '\0';
// 		first_part = ft_strjoin(first_part, str);
// 		printf("firs part = %s\n", first_part);
// 		sleep(1);
// 		return (first_part);
// 	}
// 	return (NULL);
// }