/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 10:36:15 by nettalha          #+#    #+#             */
/*   Updated: 2023/06/06 14:34:42 by nettalha         ###   ########.fr       */
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

// t_env	*ft_envnew(char *key, char *value, int is_equ)
// {
// 	t_env	*node;

// 	node = (t_env *)malloc(sizeof(t_env));
// 	if (!node)
// 		return (0);
// 	node->value = value;
// 	node->key = key;
// 	node->is_equ = is_equ;
// 	node->prev = NULL;
// 	node->next = NULL;
// 	return (node);
// }

t_env *ft_envnew(char *key, char *value, int is_equ)
{
    t_env *node = (t_env *)malloc(sizeof(t_env));
    if (!node)
        return NULL;

    node->value = (char *)malloc((strlen(value) + 1) * sizeof(char));
    if (!node->value)
    {
        free(node);
        return NULL;
    }
    ft_strcpy(node->value, value);
	// node->value = ft_strdup(value);

    node->key = (char *)malloc((strlen(key) + 1) * sizeof(char));
    if (!node->key)
    {
        free(node->value);
        free(node);
        return NULL;
    }
    ft_strcpy(node->key, key);
	// node->key = ft_strdup(key);

    node->is_equ = is_equ;
    node->prev = NULL;
    node->next = NULL;
	free(key);
	free(value);
    return node;
}

t_env	*ft_envlast(t_env *env)
{
	t_env	*current;

	current = env;
	if (current == NULL)
		return (NULL);
	while (current->next)
		current = current->next;
	return (current);
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

void	ft_enviter(t_env *env, void (*f)(void *))
{
	if (!env || !f)
		return ;
	while (env)
	{
		f(env->value);
		env = env->next;
	}
}

// void	ft_envdelone(t_env *env, void (*del)(void *))
// {
// 	if (!env || !del)
// 		return ;
// 	del(env->key);
// 	del(env->key);
// 	free(env);
// }

void	ft_envdelone(char* str, t_env **env)
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
			break;
		}
		current = current->next;
	}
}

void	ft_envclear(t_env **env, void (*del)(void *))
{
	t_env	*current;
	t_env	*next;

	current = *env;
	while (current)
	{
		next = current->next;
		del(current->key);
		del(current->value);
		free(current);
		current = next;
	}
	*env = NULL;
}

void	ft_upenv(char *key, char *value, t_env *envp)
{
	t_env	*current;

	// printf("error here\n");
	current = envp;
	while(current)
	{
		if(!ft_strcmp(current->key, key))
			break ;
		current = current->next;
	}
	current->value = ft_strdup(value);
}

void	ft_printenv(t_env *env)
{
	t_env	*current;

	current = env;

	while (current != NULL)
	{
		printf("%s = %s\n", current->key, current->value);
		current = current->next;
	}
}
