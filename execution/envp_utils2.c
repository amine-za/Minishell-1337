/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:27:56 by nettalha          #+#    #+#             */
/*   Updated: 2023/06/20 17:30:17 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_upenv(char *key, char *value, t_env *envp)
{
	t_env	*current;

	current = envp;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
			break ;
		current = current->next;
	}
	current->value = ft_strdup(value);
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
