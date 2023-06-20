/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_the_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:39:48 by azaghlou          #+#    #+#             */
/*   Updated: 2023/06/20 15:51:31 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	**fill_the_strings(char *s, char *ss, char *sss, char **ar)
// {
// 	char **ary;
// 	static int	i;

// 	ary = ft_calloc(sizeof(char *), 4);
// 	while (ar[i] && ar[i][0] != '|')
// 	{
// 		if ((!ft_strcmp("<", ar[i]) || !ft_strcmp(">", ar[i])
// 				|| !ft_strcmp(">>", ar[i])) && ar[i + 1])
// 		{
// 			s = ft_strjoin2(ft_strjoin2(s, " "), ar[i]);
// 			ss = ft_strjoin2(ft_strjoin2(ss, " "), ar[i + 1]);
// 		}
// 		else if ((!ft_strcmp("<<", ar[i])) && ar[i + 1])
// 		{
// 			s = ft_strjoin2(ft_strjoin2(s, " "), ar[i]);
// 			sss = ft_strjoin2(ft_strjoin2(sss, " "), ar[i + 1]);
// 		}
// 		i++;
// 	}
// 	if (ar[i] && ar[i][0] == '|')
// 		i++;
// 	if (!ar[i])
// 		i = 0;
// 	ary[0] = s;
// 	ary[1] = ss;
// 	ary[2] = sss;
// 	return (ary);
// }

int	*count_red(char **ar)
{
	int	i;
	int	*count;

	i = 0;
	count = malloc(sizeof(int) * 3);
	count[0] = 0;
	count[1] = 0;
	count[2] = 0;
	while (ar[i] && ar[i][0] != '|')
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
		i++;
	}
	return (count);
}

void	fill_red(t_cmd *cmd, char **ar)
{
	static int	i;
	int	j;
	int	k;
	int	*red_nb;

	j = 0;
	k = 0;
	red_nb = count_red(ar);
	cmd->red = ft_calloc(sizeof(char *), red_nb[0] + 1);
	cmd->file = ft_calloc(sizeof(char *), red_nb[1] + 1);
	cmd->delimiter = ft_calloc(sizeof(char *), red_nb[2] + 1);
	while (ar[i] && ar[i][0] != '|')
	{
		if ((!ft_strcmp("<", ar[i]) || !ft_strcmp(">", ar[i])
				|| !ft_strcmp(">>", ar[i])) && ar[i + 1])
		{
			cmd->red[j] = ft_strdup(ar[i]);
			cmd->file[j] = ft_strdup(ar[i + 1]);
			j++;
		}
		else if ((!ft_strcmp("<<", ar[i])) && ar[i + 1])
		{
			cmd->red[j] = ft_strdup(ar[i]);
			cmd->delimiter[k] = ft_strdup(ar[i + 1]);
			j++;
			k++;
		}
		i++;
	}
	if (!ar[i])
		i = 0;
	else if (ar[i][0] == '|')
		i++;
	// if (j > 0)
	// {cmd->red[j] = NULL;
	// cmd->file[j] = NULL;}
	// if (k > 0)
	// 	cmd->delimiter[j] = NULL;
}

// void	redirec_fill(t_cmd *cmd, char **ar)
// {
// 	// char		*s;
// 	// char		*ss;
// 	// char		*sss;
// 	// char 		**ary ;

// 	// s = NULL;
// 	// ss = NULL;
// 	// sss = NULL;
// 	cmd->red = NULL;
// 	cmd->file = NULL;
// 	cmd->delimiter = NULL;
// 	if (count_red(ar)[0])
// 		fill_red(cmd, ar);
// 	// ary = fill_the_strings(s, ss, sss, ar);
// 	// if (ary[0])
// 	// 	cmd->red = ft_split(ary[0], ' ');
// 	// if (ary[1])
// 	// 	cmd->file = ft_split(ary[1], ' ');
// 	// if (ary[2])
// 	// 	cmd->delimiter = ft_split(ary[2], ' ');
// 	if (!cmd->red)
// 		printf("yes\n");
// 	if (!cmd->file)
// 		printf("yes\n");
// 	if (!cmd->delimiter)
// 		printf("yes\n");
// }

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
			// ll->cmd[j] = NULL;
			i++;
			break ;
		}
		ll->cmd[j++] = rm_quotes(ar[i++], 0);
	}
	if (!ar[i])
	{
		// ll->cmd[j] = NULL;
		i = 0;
	}
	return (j);
}

t_cmd	*add_new(char **ar, t_cmd *prev)
{
	t_cmd	*ll;
	int		j;

	j = 0;
	ll = malloc(sizeof(t_cmd));
	ll->Rpipe = 0;
	ll->prev = prev;
	while (ar[j] && ar[j][0] && ar[j][0] != '|')
		j++;
	ll->cmd = ft_calloc(sizeof(char *), j + 2);
	fill_red(ll, ar);
	j = 0;
	j = content_fill(ll, ar, j);
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