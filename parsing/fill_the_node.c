/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_the_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:39:48 by azaghlou          #+#    #+#             */
/*   Updated: 2023/06/24 11:03:00 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*count_red(char **ar)
{
	int	i;
	int	*count;

	i = -1;
	count = malloc(sizeof(int) * 3);
	count[0] = 0;
	count[1] = 0;
	count[2] = 0;
	// printf("					%s\n", ar[i]);
	while (ar[++i] && ar[i][0] != '|')
	{
		if ((!ft_strcmp("<", ar[i]) || !ft_strcmp(">", ar[i])
				|| !ft_strcmp(">>", ar[i])))
		{
			count[0]++;
			if (ar[i + 1])
				count[1]++;
		}
		else if (!ft_strcmp("<<", ar[i]))
		{
			count[0]++;
			if (ar[i + 1])
				count[2]++;
		}
	}
	return (count);
}

int	searche_for_red_and_fill(char **ar, t_cmd *cmd, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (ar[i] && ar[i][0] != '|')
	{
		if ((!ft_strcmp("<", ar[i]) || !ft_strcmp(">", ar[i])
				|| !ft_strcmp(">>", ar[i])) && ar[i + 1])
		{
			free(cmd->red[j + k]);
			cmd->red[j + k] = ft_strdup(ar[i]);
			free(cmd->file[j]);
			cmd->file[j++] = ft_strdup(ar[i + 1]);
		}
		else if ((!ft_strcmp("<<", ar[i])) && ar[i + 1])
		{
			free(cmd->red[j + k]);
			cmd->red[j + k] = ft_strdup(ar[i]);
			free(cmd->delimiter[k]);
			cmd->delimiter[k++] = ft_strdup(ar[i + 1]);
		}
		i++;
	}
	return (i);
}

void	fill_red(t_cmd *cmd, char **ar)
{
	static int	i;
	int	*red_nb;

	red_nb = count_red(&ar[i]);
	cmd->red = ft_calloc(sizeof(char *), red_nb[0] + 2);
	if (red_nb[1] > 0)
		cmd->file = ft_calloc(sizeof(char *), red_nb[1] + 2);
	if (red_nb[2] > 0)
		cmd->delimiter = ft_calloc(sizeof(char *), red_nb[2] + 2);
	i = searche_for_red_and_fill(ar, cmd, i);
	if (!ar[i])
		i = 0;
	else if (ar[i][0] == '|')
		i++;
	free(red_nb);
}

int	content_fill(t_cmd *ll, char **ar, int j)
{
	static int	i;

	while (ar[i])
	{
		if (ar[i][0] == '>' || ar[i][0] == '<')
		{
			i += 2;
			if (ar[i - 1] && ar[i])
				continue ;
			i = 0;
			break ;
		}
		if (ar[i][0] == '|')
		{
			ll->Rpipe = 1;
			i++;
			break ;
		}
		ll->cmd[j++] = rm_quotes(ar[i++]);
	}
	if (!ar[i])
		i = 0;
	return (j);
}

t_cmd	*add_new(char **ar, t_cmd *prev)
{
	int		j;
	t_cmd	*ll;

	j = 0;
	ll = malloc(sizeof(t_cmd));
	ll->red = NULL;
	ll->file = NULL;
	ll->delimiter = NULL;
	ll->Rpipe = 0;
	ll->prev = prev;
	while (ar[j] && ar[j][0] && ar[j][0] != '|')
		j++;
	ll->cmd = ft_calloc(sizeof(char *), j + 2);
	// red_nb = count_red(ar);
	// if (red_nb[0])
	fill_red(ll, ar);
	j = 0;
	j = content_fill(ll, ar, j);
	return (ll);
}
