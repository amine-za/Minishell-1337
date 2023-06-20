/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:21:30 by azaghlou          #+#    #+#             */
/*   Updated: 2023/06/20 13:09:18 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*rm_quotes(char *s, int flag)
{
	int		i;
	int		j;
	t_inf	p;
	char	*str;

	i = -1;
	j = 0;
	p.in_sgl = 0;
	p.in_dbl = 0;
	str = calloc(1, ft_strlen(s) + 1);
	while (s[++i])
	{
		if (s[i] == '\'' && p.in_dbl == 0)
			p.in_sgl = cls_or_opn_qt(p.in_sgl);
		else if (s[i] == '\"' && p.in_sgl == 0)
			p.in_dbl = cls_or_opn_qt(p.in_dbl);
		else
			str[j++] = s[i];
	}
	if (flag == 1 && (p.in_sgl == 1 || p.in_dbl == 1))
	{
		free(str);
		return (NULL);
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

void	print_ll(t_cmd *ll)
{
	int	i;

	i = 0;
	while (ll)
	{
		printf("\n--------%d--------\n", i);
		for (int x = 0; ll->cmd[x]; x++)
			printf("[%s] ", ll->cmd[x]);
		printf("\n");
		printf("Lpipe = %d || Rpipe = %d\n", ll->Lpipe, ll->Rpipe);
		// printf("err = %d\n", ll->err);
		if (ll->red)
		{
			printf("\nred --> ");
			for (int x = 0; ll->red[x]; x++)
				printf("[%s] ", ll->red[x]);
			printf("\nfile --> ");
			for (int x = 0; ll->file[x]; x++)
				printf("[%s] ", ll->file[x]);
			printf("\ndelimiter --> ");
			for (int x = 0; ll->delimiter[x]; x++)
				printf("[%s] ", ll->delimiter[x]);
		}
		printf("-----------------\n");
		ll = ll->next;
		i++;
	}
}
