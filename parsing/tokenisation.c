/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:22:16 by azaghlou          #+#    #+#             */
/*   Updated: 2023/06/24 14:59:46 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	t_glbl_var_fct(int j, int flag)
{
	static int	sttc;

	if (flag == 1)
		sttc = j;
	return (sttc);
}

void	remove_empty_args(char **ar)
{
	int	j;

	j = 0;
	while (ar[j])
	{
		if (!ar[j][0])
		{
			while (ar[j + 1])
			{
				ar[j] = ar[j + 1];
				j++;
			}
			ar[j] = NULL;
			j = 0;
		}
		j++;
	}
}

char	**tokenisation(char **ar, char *s, t_inf p)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (if_append_or_herdoc(s, &i, &p))
			ar = case_of_append_or_herdoc(ar, s, &i);
		else if (if_pipe_or_red(s, &i, &p))
			ar = case_of_red_or_pipe(ar, s, &i);
		else if (s[i] == '\'' && p.in_dbl == 0)
			ar = case_of_sgl_quote(ar, s, &i, &p);
		else if (s[i] == '\"' && p.in_sgl == 0)
			ar = case_of_dbl_quotes(ar, s, &i, &p);
		else if (s[i] == ' ' && p.in_dbl == 0 && p.in_sgl == 0)
			case_of_space(&i);
		else if (s[i] == '\n')
			break ;
		else
			ar = els(ar, s, &i);
	}
	return (ar);
}

char	**check_and_token(char *s, t_env *env)
{
	t_inf	p;
	char	**ar;

	p.in_sgl = 0;
	p.in_dbl = 0;
	ar = ft_calloc(sizeof(char *), 1);
	ar = tokenisation(ar, s, p);
	remove_empty_args(ar);
	if (syntaxe_err(ar) == 1)
	{
		ft_free(ar);
		return (NULL);
	}
	ar = var_case(ar, env);
	return (ar);
}
