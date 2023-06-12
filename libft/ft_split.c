/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_split.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nettalha <nettalha@student.1337.ma>		+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/10/05 18:30:39 by nettalha		  #+#	#+#			 */
/*   Updated: 2023/05/04 16:22:33 by nettalha		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	countwords(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count + 1);
}

int	countletter(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i + 1);
}

char	**ft_split(const char *s, char c)
{
	char	**ptr;
	int		i;
	int		j;

	ptr = malloc((countwords(s, c)) * sizeof(char *));
	if (!ptr)
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		while (*s != '\0' && *s == c)
			s++;
		if (*s)
		{
			ptr[i] = malloc(countletter(s, c) * sizeof(char));
			j = 0;
			while (*s != '\0' && *s != c)
				ptr[i][j++] = *s++;
			ptr[i][j] = '\0';
			i++;
		}
	}
	ptr[i] = NULL;
	return (ptr);
}

char	**ft_splitv2(const char *s, char c)
{
	char	**ptr;
	int		i;

	ptr = malloc(3 * sizeof(char *));
	if (!ptr)
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		while (*s != '\0' && *s == c)
			s++;
		if (*s)
		{
			ptr[i] = malloc((countletter(s, c) + 1) * sizeof(char));
			ft_strlcpy(ptr[i], s, countletter(s, c));
			s += countletter(s, c);
			i++;
			break ;
		}
	}
	ptr[i] = malloc((ft_strlen(s) + 1) * sizeof(char));
	ft_strlcpy(ptr[i], s, ft_strlen(s) + 1);
	ptr[++i] = NULL;
	return (ptr);
}
