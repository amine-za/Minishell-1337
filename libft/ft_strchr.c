/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:45:16 by nettalha          #+#    #+#             */
/*   Updated: 2023/05/04 13:23:19 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c && *s != '\0')
		s++;
	if (*s == (char)c)
		return ((char *)s);
	else
		return (NULL);
}

char	ft_strchrv2(const char *s, int c1, int c2)
{
	while (*s != (char)c1 && *s != (char)c2 && *s != '\0')
		s++;
	if (*s == (char)c1)
		return (*s);
	if (*s == (char)c2)
		return (*s);
	else
		return (0);
}

int	ft_strchr_count(const char *s, int c)
{
	int	count;

	count = 0;
	while (*s != '\0')
	{
		if (*s == (char)c)
			count++;
		s++;
	}
	return (count);
}
