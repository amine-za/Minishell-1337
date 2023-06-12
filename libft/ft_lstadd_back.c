/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 20:07:26 by nettalha          #+#    #+#             */
/*   Updated: 2023/05/02 10:10:09 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node;

	if (*lst == NULL)
	{
		new->prev = NULL;
		*lst = new;
	}
	else
	{
		node = ft_lstlast(*lst);
		node->next = new;
		new->prev = node;
	}
}
