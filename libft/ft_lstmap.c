/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:01:21 by nettalha          #+#    #+#             */
/*   Updated: 2023/05/02 10:33:37 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*node;

	new = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		node = ft_lstnew(f(lst->data));
		if (!node)
			ft_lstclear(&new, del);
		ft_lstadd_back(&new, node);
		lst = lst->next;
	}
	return (new);
}
