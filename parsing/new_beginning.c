/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_beginning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 23:14:37 by azaghlou          #+#    #+#             */
/*   Updated: 2023/06/05 18:19:08 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cls_or_opn_qt(int qt)
{
	if (qt == 1)
		return(0);
	if (qt == 0)
		return(1);
	return (0);
}

//this function join a character to the last argument of an 2d array

char	**chrjoin(char **s, char c, int flag)
{
	int		i;
	int		j;
	int		len;
    char    *str;
	char	**ar;

	i = 0;
	j = 0;
	len = 0;
	while (s[len++]){}
	len--;
	if (flag == 1 || s[0] == NULL)
	{
		ar = malloc (sizeof (char *) * (len + 2));
		ar[len+1] = NULL;
		while (i < len)
		{
			ar[i] = calloc(1, ft_strlen(s[i]));
			i++;
		}
		ar[i] = calloc(1, 2);
		i = 0;
		while (s[0] && s[i])
		{
			while(s[i][j])
			{
				ar[i][j] = s[i][j];
				j++;
			}
			ar[i][j] = '\0';
			j = 0;
			i++;
		}
		ar[i][0] = c;
		ar[i][1] = '\0';
		while(s[j])
			free(s[j++]);
		free(s);
		return(ar);
	}
	ar = malloc (sizeof (char *) * (len + 1));
	ar[len] = NULL;
	while (i < len-1)
	{
		ar[i] = calloc(1, ft_strlen(s[i])+1);
		i++;
	}
	ar[i] = calloc(1, ft_strlen(s[i]) + 2);
	str = calloc(1, ft_strlen(s[i]) + 2);
	i = 0;
	while (i < len)
	{
		while(s[i][j])
		{
			ar[i][j] = s[i][j];
			j++;
		}
		ar[i][j] = '\0';
		j = 0;
		i++;
	}
	i = 0;
	while(s[len-1][i])
    {
		str[i] = s[len-1][i];
        i++;
    }
	str[i] = c;
	free(ar[len-1]);
    ar[len-1] = str;
	while (j < len)
		free(s[j++]);
	free(s);
	return (ar);
}

char	*erase_spaces(char *s)
{
	int i;
	int j;
	t_inf p;
	char *ss;

	i = 0;
	j = 0;
	p.in_sgl = 0;
	p.in_dbl = 0;
	ss = malloc (ft_strlen (s) + 1);
	while (s[i])
	{
		if (s[i] == '\'' && p.in_dbl == 0)
			p.in_sgl = cls_or_opn_qt(p.in_sgl);
		else if (s[i] == '\"' && p.in_sgl == 0)
			p.in_dbl = cls_or_opn_qt(p.in_dbl);
		if ((p.in_dbl == 0 && p.in_sgl == 0 && s[i-1] == ' ' && s[i] == ' ')
				|| (j == 0 && s[i] == ' '))
			i++;
		else
			ss[j++] = s[i++];
	}
	ss[j] = '\0';
	return (ss);
}

//Devide the whole commande to parts in every space or quotes or pipe or redirection//

char	**tokenisation(char *s, t_env *env)
{
	int i;
	int j;
	t_inf p;
	char **ar;

	i = 0;
	j = 0;
	p.in_sgl = 0;
	p.in_dbl = 0;
	ar = malloc (sizeof(char *));
	ar[0] = NULL;
	while(s[i])
	{
		if (s[i+1] && ((s[i] == '<' && s[i+1] == '<' && p.in_dbl == 0 && p.in_sgl == 0)
				|| (s[i] == '>' && s[i+1] == '>' && p.in_dbl == 0 && p.in_sgl == 0)))
		{
			ar = chrjoin(ar, s[i++], 1);
			ar = chrjoin(ar, s[i++], 0);
			j = 1;
		}
		else if ((s[i] == '|' || s[i] == '<' || s[i] == '>')
					&& p.in_dbl == 0 && p.in_sgl == 0)
		{
			ar = chrjoin(ar, s[i++], 1);
			j = 0;
			if (s[i-1] != '|' && s[i-1] && s[i+1] && !(s[i] == '>' && s[i-1] == '<')
				&& !(s[i] == '<' && s[i-1] == '>')
				&& !(s[i-1] == '>' && s[i] == ' ' && s[i+1] == '<')
				&& !(s[i-1] == '<' && s[i] == ' ' && s[i+1] == '>'))
				j = 1;
		}
		else if(s[i] == '\'' && p.in_dbl == 0)
		{
			p.in_sgl = cls_or_opn_qt(p.in_sgl);
			if (p.in_sgl == 1 && s[i-1] == ' ')
				j = 1;
			ar = chrjoin(ar, s[i++], j);
			j = 0;
		}
		else if(s[i] == '\"' && p.in_sgl == 0)
		{
			p.in_dbl = cls_or_opn_qt(p.in_dbl);
			if (p.in_dbl == 1 && s[i-1] == ' ')
				j = 1;
			ar = chrjoin(ar, s[i++], j);
			j = 0;
		}
		else if(s[i] == ' ' && p.in_dbl == 0 && p.in_sgl == 0)
		{
			j = 1;
			i++;
		}
		else if (s[i] == '\n')
			break;
		else
		{
			ar = chrjoin(ar, s[i++], j);
			j = 0;
		}
	}
	j = 0;
	while (ar[j])
	{
		if (!ar[j][0])
		{
			while (ar[j+1])
			{
				ar[j] = ar[j+1];
				j++;
			}
			ar[j] = NULL;
			j = 0;
		}
		j++;
	}
	j = 0;
	if (syntaxe_err(ar) == 1)
		return (NULL);
	ar = var_case(ar, env);
	while (ar[j])
	{
		ar[j] = rm_quotes(ar[j], 0);
		if (ar[j] == NULL)
		{
			// printf("sike\n");
			for(int x = 0; ar[x]; x++)
				free(ar[x]);
			free(ar);
			return (NULL);
		}
		j++;
	}
	// for(int x = 0; ar[x]; x++)
	// 	printf("|%s|\n", ar[x]);
	// printf("\n\n");
	return(ar);
}

t_cmd	*parsing1(char *s, t_env *env)
{
	int			i;
	char		**ar;
	t_cmd		*ll;
	t_cmd		*head;

	i = 0;
	// while (env)
	// {
	// 	printf("|%s|\n", env->value);
	// 	env = env->next;
	// }
	// exit(0);
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
	while(i < count_pipes(s))
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
	ft_free(ar);
	// free(ar);
	free(s);
	// print_ll(ll);
	return(head);
}

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
