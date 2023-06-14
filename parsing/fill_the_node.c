/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_the_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:39:48 by azaghlou          #+#    #+#             */
/*   Updated: 2023/06/14 19:19:46 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirec_fill(t_cmd *cmd, char **ar)
{
	static int i;
	char *s = ft_strdup(" ");
	char *ss = ft_strdup(" ");
	char *sss = ft_strdup(" ");

	cmd->red = NULL;
	cmd->file = NULL;
	cmd->delimiter = NULL;
	while (ar[i] && ar[i][0] != '|')
	{
		if ((!ft_strcmp("<", ar[i]) || !ft_strcmp(">", ar[i]) || !ft_strcmp(">>", ar[i])) && ar[i+1])
		{
			s = ft_strjoin2(ft_strjoin2(s, " "), ar[i]);
			ss = ft_strjoin2(ft_strjoin2(ss, " "), ar[i+1]);
		}
		else if ((!ft_strcmp("<<", ar[i])) && ar[i+1])
		{
			s = ft_strjoin2(ft_strjoin2(s, " "), ar[i]);
			sss = ft_strjoin2(ft_strjoin2(sss, " "), ar[i+1]);
		}
		i++;
	}
	if (!ar[i])
		i = 0;
	if (ar[i] && ar[i][0] == '|')
		i++;
	if (s)
	{
		cmd->red = ft_split(s, ' ');
		free(s);
	}
	if (ss)
	{
		cmd->file = ft_split(ss, ' ');
		free(ss);
	}
	if (sss)
	{
		cmd->delimiter = ft_split(sss, ' ');
		free(sss);
	}
}

int	*count_red(char **ar)
{
	int i;
	int	*ir;

	i = 0;
	ir = malloc (sizeof(int) * 3);
	ir[0] = 0;
	ir[1] = 0;
	ir[2] = 0;
	while (ar[i] && ar[i][0] != '|')
	{
		if (ar[i][0] == '>')
		{
			ir[0]++;
			ir[1]++;
		}
		else if (ar[i][0] == '<')
		{
			ir[0]++;
			ir[2]++;
		}
		i++;
	}
	return (ir);
}

t_cmd	*add_new(char **ar, t_cmd *prev)
{
	static int	i;
	t_cmd		*ll;
	int			j;

	j = 0;
	ll = malloc(sizeof(t_cmd));
	ll->Rpipe = 0;
	ll->prev = prev;
	while (ar[j] && ar[j][0] != '|')
		j++;
	ll->cmd = malloc (sizeof (char *) * j+1);
	redirec_fill(ll, ar);
	j = 0;
	while (ar[i])
	{
		if (ar[i][0] == '>' || ar[i][0] == '<')
		{
			i += 2;
			if (ar[i-1] && ar[i])
				continue;
			else
			{
				i = 0;
				break;
			}
		}
		if (ar[i][0] == '|')
		{
			ll->Rpipe = 1;
			ll->cmd[j] = NULL;
			i++;
			break;
		}
		ll->cmd[j++] = rm_quotes(ar[i], 0);
		i++;
	}
	ll->cmd[j] = NULL;
	if (!ar[i])
		i = 0;
	return (ll);
}

// void	malloc_the_node(t_cmd *ll, char **ar)
// {
// 	int	j;
// 	int	x;

// 	j = 0;
// 	x = 0;
// 	ll = malloc(sizeof(t_cmd));
// 	ll->red = malloc(sizeof(char *) * count_red(ar)[0]);
// 	ll->file = malloc (sizeof(char *) * count_red(ar)[1]);
// 	ll->delimiter = malloc (sizeof(char *) * count_red(ar)[2]);
// 	while (ar[j] && ar[j][0] != '|')
// 		j++;
// 	ll->cmd = malloc (sizeof(char *) * j + 1);
// 	while (x < j-1)
// 		ll->cmd[x++] = calloc(1, 4 + 1);
// 	ll->cmd[x] = NULL;
// 	j = 0;
// 	while (j < count_red(ar)[0])
// 		ll->red[j++] = calloc(1, 4);
// 	ll->red[j] = NULL;
// 	ll->Rpipe = 0;
// }

// ls > file0 < file1 << kk << nn >> file2
// ls > file0 > file1 | < file2 < file3 | >> file4 >> file5 | << cc << nn << kk




// void	redirec_fill(t_cmd *ll, char **s, int in)
// {
// 	static int	i;
// 	static int	j;
// 	static int	y;

// 	if (ft_strcmp(s[in], "<<") == 0)
// 	{
// 		ll->red[i++] = s[in];
// 		// ll->delimiter[j] = calloc (1, ft_strlen(s[in]));
// 		ll->delimiter[j++] = s[in+1];
// 		printf("red : %s || delimiter : %s\n", ll->red[i-1], ll->delimiter[j-1]);
// 	}
// 	else if (s[in][0] == '>' || s[in][0] == '<')
// 	{
// 		ll->red[i++] = s[in];
// 		// ll->file[y] = calloc (1, ft_strlen(s[in]));
// 		ll->file[y++] = s[in+1];
// 		printf("red : %s || file : %s\n", ll->red[i-1], ll->file[y-1]);
// 	}
// 	if (s[in+2] && s[in+2][0] == '|')
// 	{
// 		printf("\n\n");
// 		ll->red[i] = NULL;
// 		ll->file[y] = NULL;
// 		ll->delimiter[j] = NULL;
// 		i = 0;
// 		j = 0;
// 		y = 0;
// 	}
// 	//test
// }

	// int x = 0;
	// ll = NULL;
	// malloc_the_node(ll, &ar[i]);

	// ll->red = NULL;
	// ll->file = NULL;
	// ll->delimiter = NULL;
	// if (count_red(ar)[0] > 0)
	// 	ll->red = malloc(sizeof(char *) * count_red(ar)[0]);
	// if (count_red(ar)[1] > 0)
	// 	ll->file = malloc (sizeof(char *) * count_red(ar)[1]);
	// if (count_red(ar)[2] > 0)
	// 	ll->delimiter = malloc (sizeof(char *) * count_red(ar)[2]);
	// fill_with_null(ar, ll->red, ll->file, ll->delimiter);
	// ll->red[count_red(ar)[0]-1] = NULL;
	// ll->file[count_red(ar)[1]-1] = NULL;
	// ll->delimiter[count_red(ar)[2]-1] = NULL;

	// while (ar[j] && ar[j][0] != '|')
	// 	j++;
	// ll->cmd = malloc (sizeof(char *) * j + 1);
	// while (x < j)
	// 	ll->cmd[x++] = calloc(1, 4 + 1);
	// ll->cmd[x] = NULL;
	// j = 0;
	// while (j < count_red(ar)[0])
	// 	ll->red[j++] = calloc(1, 4);