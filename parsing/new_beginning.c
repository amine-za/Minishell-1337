/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_beginning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 23:14:37 by azaghlou          #+#    #+#             */
/*   Updated: 2023/06/21 18:11:54 by azaghlou         ###   ########.fr       */
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
		if ((p.in_dbl == 0 && p.in_sgl == 0
				&& i > 0 && s[i - 1] == ' ' && s[i] == ' ')
			|| (j == 0 && s[i] == ' '))
			i++;
		else
			ss[j++] = s[i++];
	}
	return (ss);
}

t_cmd	*fill_linked_list(t_cmd *ll, char **ar, int i, int count)
{
	t_cmd	*head;

	head = ll;
	while (++i < count)
	{
		ll->next = add_new(ar, ll);
		ll = ll->next;
		ll->Lpipe = 0;
		if (ll->prev->Rpipe == 1)
			ll->Lpipe = 1;
	}
	ll->next = NULL;
	// ft_free(ar);
	return (head);
}

t_cmd	*parsing1(char *s, t_env *env)
{
	int		i;
	char	**ar;
	t_cmd	*ll;
	t_cmd	*head;

	i = -1;
	s = erase_spaces(s);
	ar = check_and_token(s, env);
	if (ar == NULL)
	{
		free(s);
		return (NULL);
	}
	ll = add_new(ar, NULL);
	head = ll;
	ll->Lpipe = 0;
	ll = fill_linked_list(ll, ar, i, count_pipes(s));
	ll = head;
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
