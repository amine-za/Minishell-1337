/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 10:36:15 by nettalha          #+#    #+#             */
/*   Updated: 2023/06/20 17:28:51 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_envsize(t_env *env)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		env = env->next;
		i++;
	}
	return (i);
}

void	ft_free2(void *s1, void *s2)
{
	free(s1);
	free(s2);
}

t_env	*ft_envnew(char *key, char *value, int is_equ)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->value = (char *)malloc((strlen(value) + 1) * sizeof(char));
	if (!node->value)
		return (free(node), NULL);
	ft_strcpy(node->value, value);
	node->key = (char *)malloc((strlen(key) + 1) * sizeof(char));
	if (!node->key)
	{
		ft_free2(node->value, node);
		return (NULL);
	}
	ft_strcpy(node->key, key);
	node->is_equ = is_equ;
	node->prev = NULL;
	node->next = NULL;
	ft_free2(key, value);
	return (node);
}

t_env	*ft_envadd_back(t_env *env, t_env *new_node)
{
	t_env	*node;

	if (env == NULL)
		env = new_node;
	else
	{
		node = ft_envlast(env);
		node->next = new_node;
		new_node->prev = node;
	}
	return (env);
}

void	ft_envdelone(char *str, t_env **env)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (!ft_strcmp(current->key, str))
		{
			if (current->prev)
				current->prev->next = current->next;
			if (current->next)
				current->next->prev = current->prev;
			if (current == *env)
				*env = current->next;
			free(current);
			break ;
		}
		current = current->next;
	}
}
