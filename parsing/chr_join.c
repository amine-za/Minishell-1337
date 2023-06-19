/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chr_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:42:54 by azaghlou          #+#    #+#             */
/*   Updated: 2023/06/19 17:52:47 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		ar = ft_calloc(sizeof(char *), (len + 2));
		while (i < len)
		{
			ar[i] = ft_calloc(1, ft_strlen(s[i]) + 1);
			i++;
		}
		ar[i] = ft_calloc(1, 2);
		i = 0;
		while (s[i])
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
		ft_free(s);
		return (ar);
	}
	ar = ft_calloc(sizeof(char *), (len + 1));
	while (i < len - 1)
	{
		ar[i] = ft_calloc(1, ft_strlen(s[i]) + 1);
		i++;
	}
	ar[i] = ft_calloc(1, ft_strlen(s[i]) + 2);
	str = ft_calloc(1, ft_strlen(s[i]) + 2);
	i = 0;
	while (s[i])
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
	i--;
	j = 0;
	while (s[i] && s[i][j])
	{
		str[j] = s[i][j];
		j++;
	}
	str[j] = c;
	ar[i] = str;
	ft_free(s);
	return (ar);
}