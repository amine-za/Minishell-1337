/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chr_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:42:54 by azaghlou          #+#    #+#             */
/*   Updated: 2023/06/21 18:25:42 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**add_an_arg(char **ar, char **s, char c, int len)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	ar = ft_calloc(sizeof(char *), (len + 2));
	while (++i < len)
		ar[i] = ft_calloc(1, ft_strlen(s[i]) + 1);
	ar[i] = ft_calloc(1, 2);
	i = -1;
	while (s[++i])
	{
		while (s[i][++j])
			ar[i][j] = s[i][j];
		j = -1;
	}
	ar[i][0] = c;
	ft_free(s);
	return (ar);
}

char	**add_in_the_last_arg(char **ar, char **s, char c, int len)
{
	int		i;
	int		j;
	char	*str;

	i = -1;
	j = -1;
	ar = ft_calloc(sizeof(char *), (len + 1));
	while (++i < len - 1)
		ar[i] = ft_calloc(1, ft_strlen(s[i]) + 1);
	ar[i] = ft_calloc(1, ft_strlen(s[i]) + 2);
	str = ft_calloc(1, ft_strlen(s[i]) + 2);
	i = -1;
	while (s[++i])
	{
		while (s[i][++j])
			ar[i][j] = s[i][j];
		j = -1;
	}
	i--;
	while (s[i] && s[i][++j])
		str[j] = s[i][j];
	str[j] = c;
	free(ar[i]);
	ar[i] = str;
	ft_free(s);
	return (ar);
}

char	**chrjoin(char **s, char c, int flag)
{
	int		len;
	char	**ar;

	len = 0;
	ar = NULL;
	while (s[len++])
	{
	}
	len--;
	if (flag == 1 || s[0] == NULL)
		return (add_an_arg(ar, s, c, len));
	return (add_in_the_last_arg(ar, s, c, len));
}

	// ar[i] = ft_calloc(1, ft_strlen(s[i]) + 2);
	// str = ft_calloc(1, ft_strlen(s[i]) + 2);
	// i = 0;
	// while (s[i])
	// {
	// 	while (s[i][j])
	// 	{
	// 		ar[i][j] = s[i][j];
	// 		j++;
	// 	}
	// 	ar[i][j] = '\0';
	// 	j = 0;
	// 	i++;
	// }
	// i--;
	// j = 0;
	// while (s[i] && s[i][j])
	// {
	// 	str[j] = s[i][j];
	// 	j++;
	// }
	// str[j] = c;
	// ar[i] = str;
	// ft_free(s);
// }
