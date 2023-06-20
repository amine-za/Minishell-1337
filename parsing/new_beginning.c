/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_beginning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 23:14:37 by azaghlou          #+#    #+#             */
/*   Updated: 2023/06/20 13:34:09 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cls_or_opn_qt(int qt)
{
	if (qt == 1)
		return (0);
	if (qt == 0)
		return (1);
	return (0);
}

char	*erase_spaces(char *s)
{
	int		i;
	int		j;
	t_inf	p;
	char	*ss;

	i = 0;
	j = 0;
	p.in_sgl = 0;
	p.in_dbl = 0;
	ss = ft_calloc(1, ft_strlen(s) + 2);
	while (s[i])
	{
		if (s[i] == '\'' && p.in_dbl == 0)
			p.in_sgl = cls_or_opn_qt(p.in_sgl);
		else if (s[i] == '\"' && p.in_sgl == 0)
			p.in_dbl = cls_or_opn_qt(p.in_dbl);
		if ((p.in_dbl == 0 && p.in_sgl == 0 && i > 0 && s[i - 1] == ' ' && s[i] == ' ')
			|| (j == 0 && s[i] == ' '))
			i++;
		else
			ss[j++] = s[i++];
	}
	return (ss);
}

char	**tokenisation(char *s, t_env *env)
{
	int		i;
	int		j;
	t_inf	p;
	char	**ar;

	i = 0;
	j = 0;
	p.in_sgl = 0;
	p.in_dbl = 0;
	ar = ft_calloc(sizeof(char *), 1);
	// ar[0] = malloc(sizeof(char));
	while (s[i])
	{
		if (s[i + 1] && ((s[i] == '<' && s[i + 1] == '<' && p.in_dbl == 0
					&& p.in_sgl == 0) || (s[i] == '>' && s[i + 1] == '>'
					&& p.in_dbl == 0 && p.in_sgl == 0)))
		{
			ar = chrjoin(ar, s[i++], 1);
			ar = chrjoin(ar, s[i++], 0);
			j = 1;
		}
		else if ((s[i] == '|' || s[i] == '<' || s[i] == '>') && p.in_dbl == 0
			&& p.in_sgl == 0)
		{
			ar = chrjoin(ar, s[i++], 1);
			j = 0;
			if (i > 0 && s[i - 1] != '|' && s[i - 1] && s[i + 1]
				&& !(s[i] == '>' && s[i - 1] == '<')
				&& !(s[i] == '<' && s[i - 1] == '>')
				&& !(s[i - 1] == '>' && s[i] == ' ' && s[i + 1] == '<')
				&& !(s[i - 1] == '<' && s[i] == ' ' && s[i + 1] == '>'))
				j = 1;
		}
		else if (s[i] == '\'' && p.in_dbl == 0)
		{
			p.in_sgl = cls_or_opn_qt(p.in_sgl);
			if (p.in_sgl == 1 && i > 0 && s[i - 1] == ' ')
				j = 1;
			ar = chrjoin(ar, s[i++], j);
			j = 0;
		}
		else if (s[i] == '\"' && p.in_sgl == 0)
		{
			p.in_dbl = cls_or_opn_qt(p.in_dbl);
			if (p.in_dbl == 1 && i > 0 && s[i - 1] == ' ')
				j = 1;
			ar = chrjoin(ar, s[i++], j);
			j = 0;
		}
		else if (s[i] == ' ' && p.in_dbl == 0 && p.in_sgl == 0)
		{
			j = 1;
			i++;
		}
		else if (s[i] == '\n')
			break ;
		else
		{
			if (i > 0 && s[i - 1] == '|')
				j = 1;
			ar = chrjoin(ar, s[i++], j);
			j = 0;
		}
	}
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
	j = 0;
	i = 0;
	if (syntaxe_err(ar) == 1)
		return (NULL);
	ar = var_case(ar, env);
	while (ar[j])
	{
		if (ar[j] == NULL)
		{
			// while (ar[i])
			// 	free(ar[i++]);
			// free(ar);
			ft_free(ar);
			return (NULL);
		}
		j++;
	}
	return (ar);
}

t_cmd	*parsing1(char *s, t_env *env)
{
	int		i;
	char	**ar;
	t_cmd	*ll;
	t_cmd	*head;

	i = 0;
	s = erase_spaces(s);
	ar = tokenisation(s, env);
	if (ar == NULL)
	{
		free(s);
		return (NULL);
	}
	ll = add_new(ar, NULL);
	head = ll;
	ll->Lpipe = 0;
	while (i < count_pipes(s))
	{
		ll->next = add_new(ar, ll);
		ll = ll->next;
		ll->Lpipe = 0;
		if (ll->prev->Rpipe == 1)
			ll->Lpipe = 1;
		i++;
	}
	ll->next = NULL;
	ll = head;
	// print_ll(head);
	// ft_free(ar);
	free(s);
	return (head);
}

// echo -n hel"l'o' worl"d | grep hell|wc -l

// for(int x = 0; ar[x]; x++)
// 	printf("|%s|\n", ar[x]);
// ll = malloc (sizeof(t_cmd) * count_pipes(s) + 1);
// for(int x = 0; x <= count_pipes(s) + 1; x++)
// 	ll[x] = malloc(sizeof (t_cmd));

/*
echo -n hello world | grep wo | wc -l
echo hello world | grep wo | wc -l
echo hello world grep wo wc -l
echo -n "hello"'world' >>abyz
export kid=1412 aptx=4869 name=amine
>in echo hello world <out >to | >dd <<ff >>lj | >ab
*/
