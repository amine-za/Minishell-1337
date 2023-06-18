/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_the_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:39:48 by azaghlou          #+#    #+#             */
/*   Updated: 2023/06/17 11:59:20 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_the_strings(char *s, char *ss, char *sss, char **ar)
{
	static int	i;

	while (ar[i] && ar[i][0] != '|')
	{
		if ((!ft_strcmp("<", ar[i]) || !ft_strcmp(">", ar[i])
				|| !ft_strcmp(">>", ar[i])) && ar[i + 1])
		{
			s = ft_strjoin2(ft_strjoin2(s, " "), ar[i]);
			ss = ft_strjoin2(ft_strjoin2(ss, " "), ar[i + 1]);
		}
		else if ((!ft_strcmp("<<", ar[i])) && ar[i + 1])
		{
			s = ft_strjoin2(ft_strjoin2(s, " "), ar[i]);
			sss = ft_strjoin2(ft_strjoin2(sss, " "), ar[i + 1]);
		}
		i++;
	}
	if (ar[i] && ar[i][0] == '|')
		i++;
	if (!ar[i])
		i = 0;
}

void	redirec_fill(t_cmd *cmd, char **ar)
{
	char		*s;
	char		*ss;
	char		*sss;

	s = ft_strdup(" ");
	ss = ft_strdup(" ");
	sss = ft_strdup(" ");
	cmd->red = NULL;
	cmd->file = NULL;
	cmd->delimiter = NULL;
	fill_the_strings(s, ss, sss, ar);
	if (s)
		cmd->red = ft_split(s, ' ');
	if (ss)
		cmd->file = ft_split(ss, ' ');
	if (sss)
		cmd->delimiter = ft_split(sss, ' ');
}

// int	*count_red(char **ar)
// {
// 	int	i;
// 	int	*ir;

// 	i = 0;
// 	ir = malloc(sizeof(int) * 3);
// 	ir[0] = 0;
// 	ir[1] = 0;
// 	ir[2] = 0;
// 	while (ar[i] && ar[i][0] != '|')
// 	{
// 		if (ar[i][0] == '>')
// 		{
// 			ir[0]++;
// 			ir[1]++;
// 		}
// 		else if (ar[i][0] == '<')
// 		{
// 			ir[0]++;
// 			ir[2]++;
// 		}
// 		i++;
// 	}
// 	return (ir);
// }

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
			ll->cmd[j] = NULL;
			i++;
			break ;
		}
		ll->cmd[j++] = rm_quotes(ar[i++], 0);
	}
	if (!ar[i])
		i = 0;
	return (j);
}

t_cmd	*add_new(char **ar, t_cmd *prev)
{
	t_cmd		*ll;
	int			j;

	j = 0;
	ll = malloc(sizeof(t_cmd));
	ll->Rpipe = 0;
	ll->prev = prev;
	while (ar[j] && ar[j][0] != '|')
		j++;
	ll->cmd = malloc(sizeof(char *) * j + 1);
	redirec_fill(ll, ar);
	j = 0;
	j = content_fill(ll, ar, j);
	ll->cmd[j] = NULL;
	return (ll);
}
	// while (ar[i] && ar[i][0] != '|')
	// {
	// 	if ((!ft_strcmp("<", ar[i]) || !ft_strcmp(">", ar[i])
	// 			|| !ft_strcmp(">>", ar[i])) && ar[i + 1])
	// 	{
	// 		s = ft_strjoin2(ft_strjoin2(s, " "), ar[i]);
	// 		ss = ft_strjoin2(ft_strjoin2(ss, " "), ar[i + 1]);
	// 	}
	// 	else if ((!ft_strcmp("<<", ar[i])) && ar[i + 1])
	// 	{
	// 		s = ft_strjoin2(ft_strjoin2(s, " "), ar[i]);
	// 		sss = ft_strjoin2(ft_strjoin2(sss, " "), ar[i + 1]);
	// 	}
	// 	i++;
	// }
	// if (ar[i] && ar[i][0] == '|')
	// 	i++;
	// if (!ar[i])
	// 	i = 0;
				// while (ar[i])
	// {
	// 	if (ar[i][0] == '>' || ar[i][0] == '<')
	// 	{
	// 		i += 2;
	// 		if (ar[i - 1] && ar[i])
	// 			continue ;
	// 		else
	// 		{
	// 			i = 0;
	// 			break ;
	// 		}
	// 	}
	// 	if (ar[i][0] == '|')
	// 	{
	// 		ll->Rpipe = 1;
	// 		ll->cmd[j] = NULL;
	// 		i++;
	// 		break ;
	// 	}
	// 	ll->cmd[j++] = rm_quotes(ar[i], 0);
	// 	i++;
	// }