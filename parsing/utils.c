/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:08:58 by azaghlou          #+#    #+#             */
/*   Updated: 2023/05/28 13:31:48 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	ft_strlen(char *s)
// {
// 	int	i;

// 	i = 0;
// 	if (!s)
// 		return (0);
// 	while (s[i] != '\0')
// 		i++;
// 	return (i);
// }

char	*my_strjoin(char *s1, char *s2)
{
	char	*ss;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ss = calloc(1, (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ss)
		return (0);
	while (s1 && s1[i])
	{
		ss[i] = s1[i];
		i++;
	}
    ss[i++] = ' ';
	while (s2 && s2[j])
	{
		ss[i] = s2[j];
		j++;
		i++;
	}
	ss[i] = '\0';
	free(s1);
	return (ss);
}

int	chrch(char *s, char c)
{
	int i;
	int rs;

	i = 0;
	rs = 0;
	while(s[i])
	{
		if (s[i] == c)
			rs++;
		i++;
	}
	return (rs);
}

int	my_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
        i++;
    if (!s1[i] && !s2[i])
        return (0);
	else
		return (1);
}

// char	*ft_strdup(char *s1)
// {
// 	char	*s2;
// 	int		j;

// 	j = 0;
// 	s2 = malloc(sizeof(char) * ft_strlen(s1) + 1);
// 	if (s2 == NULL)
// 		return (NULL);
// 	while (s1[j] != '\0')
//     {
// 		s2[j] = s1[j];
//         j++;
//     }
// 	s2[j] = '\0';
// 	return (s2);
// }



char	*ft2_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s2 || !s1)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	free(s1);
	return(str);
}
