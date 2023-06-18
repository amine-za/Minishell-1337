/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chr_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:42:54 by azaghlou          #+#    #+#             */
/*   Updated: 2023/06/18 19:50:55 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	**case_one(char **ar, char **s, char c, int len)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	j = -1;
// 	ar = malloc(sizeof(char *) * (len + 1));
// 	ar[len + 1] = NULL;
// 	while (++i < len)
// 		ar[i] = ft_calloc(1, ft_strlen(s[i]));
// 	ar[i] = ft_calloc(1, 2);
// 	i = 0;
// 	while (s[0] && s[i])
// 	{
// 		while (s[i][++j])
// 			ar[i][j] = s[i][j];
// 		ar[i][j] = '\0';
// 		j = -1;
// 		i++;
// 	}
// 	ar[i][0] = c;
// 	ar[i][1] = '\0';
// 	ar[i + 1] = NULL;
// 	// ft_free(s);
// 	// for(int x = 0; ar[x]; x++)
// 	// 	printf("|%s|\n", ar[x]);
// 	return (ar);
// }

// char	**case_two(char **ar, char **s, char c, int len)
// {
// 	int		i;
// 	int		j;
// 	char	*str;

// 	i = -1;
// 	j = -1;
// 	ar = malloc(sizeof(char *) * (len + 1));
// 	ar[len] = NULL;
// 	while (++i < len - 1)
// 		ar[i] = ft_calloc(1, ft_strlen(s[i]) + 1);
// 	ar[i] = ft_calloc(1, ft_strlen(s[i]) + 2);
// 	str = ft_calloc(1, ft_strlen(s[i]) + 2);
// 	i = 0;
// 	while (i < len)
// 	{
// 		while (s[i][++j])
// 			ar[i][j] = s[i][j];
// 		ar[i][j] = '\0';
// 		j = 0;
// 		i++;
// 	}
// 	i = -1;
// 	while (s[len - 1][++i])
// 		str[i] = s[len - 1][i];
// 	str[i] = c;
// 	free(ar[len - 1]);
// 	ar[len - 1] = str;
// 	ar[len] = NULL;
// 	// free(str);
// 	// ft_free(s);
// 	// for(int x = 0; ar[x]; x++)
// 	// 	printf("|%s|\n", ar[x]);
// 	return (ar);
// }

// char	**chrjoin(char **s, char c, int flag)
// {
// 	int		i;
// 	int		j;
// 	int		len;
// 	char	*str;
// 	char	**ar;

// 	i = -1;
// 	j = -1;
// 	len = 0;
// 	(void)str;
// 	while (s[len++])
// 	{
// 	}
// 	len--;
// 	ar = NULL;
// 	if (flag == 1 || s[0] == NULL)
// 		return (case_one(ar, s, c, len));
// 	return (case_two(ar, s, c, len));
// }

char	**chrjoin(char **s, char c, int flag)
{
	int		i;
	int		j;
	int		len;
	char	*str;
	char	**ar;

	i = 0;
	j = 0;
	len = 0;
	while (s[len++])
	{
	}
	len--;
	if (flag == 1 || s[0] == NULL)
	{
		ar = malloc(sizeof(char *) * (len + 2));
		ar[len + 1] = NULL;
		while (i < len)
		{
			ar[i] = ft_calloc(1, ft_strlen(s[i]));
			i++;
		}
		ar[i] = ft_calloc(1, 2);
		i = 0;
		while (s[0] && s[i])
		{
			while (s[i][j])
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
		ar[i + 1] = NULL;
		ft_free(s);
		return (ar);
	}
	ar = malloc(sizeof(char *) * (len + 1));
	ar[len] = NULL;
	while (i < len - 1)
	{
		ar[i] = ft_calloc(1, ft_strlen(s[i]) + 1);
		i++;
	}
	ar[i] = ft_calloc(1, ft_strlen(s[i]) + 2);
	str = ft_calloc(1, ft_strlen(s[i]) + 2);
	i = 0;
	while (i < len)
	{
		while (s[i][j])
		{
			ar[i][j] = s[i][j];
			j++;
		}
		ar[i][j] = '\0';
		j = 0;
		i++;
	}
	i = 0;
	while (s[len - 1][i])
	{
		str[i] = s[len - 1][i];
		i++;
	}
	str[i] = c;
	ar[len - 1] = str;
	ar[len] = NULL;
	ft_free(s);
	return (ar);
}

// 	ar = malloc(sizeof(char *) * (len + 1));
// 	ar[len] = NULL;
// 	while (++i < len - 1)
// 		ar[i] = ft_calloc(1, ft_strlen(s[i]) + 1);
// 	ar[i] = ft_calloc(1, ft_strlen(s[i]) + 2);
// 	str = ft_calloc(1, ft_strlen(s[i]) + 2);
// 	i = 0;
// 	while (i < len)
// 	{
// 		while (s[i][++j])
// 			ar[i][j] = s[i][j];
// 		ar[i][j] = '\0';
// 		j = 0;
// 		i++;
// 	}
// 	i = -1;
// 	while (s[len - 1][++i])
// 		str[i] = s[len - 1][i];
// 	str[i] = c;
// 	ar[len - 1] = str;
// 	ar[len] = NULL;
// 	// ft_free(s);
// 	return (ar);
// }
