/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:31:52 by nettalha          #+#    #+#             */
/*   Updated: 2023/06/23 13:12:40 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_envadd(char	**s, int is_equ, t_env *envp)
{
	if (check_key(s[0]))
		ft_envadd_back(envp, ft_envnew(s[0], s[1], is_equ));
	else
		ft_error(s[0], "not a valid identifier", 1);
	free(s);
}

t_env	*ft_setenv(char *str, t_env *envp)
{
	char	**s;
	t_env	*current;
	int		is_equ;

	current = envp;
	is_equ = 0;
	if (ft_strchr(str, '='))
		is_equ = 1;
	s = ft_splitv2(str, '=');
	if (!s)
		return (NULL);
	while (current)
	{
		if (!ft_strcmp(current->key, s[0]))
		{
			if (ft_strcmp(s[1], "") || is_equ == 1)
			{
				free(current->value);
				current->value = ft_strdup(s[1]);
			}
			ft_free(s);
			current->is_equ = is_equ;
			return (envp);
		}
		current = current->next;
	}
	ft_envadd(s, is_equ, envp);
	return (envp);
}

t_env	*env_to_struct(char **envp)
{
	int		i;
	t_env	*env;
	char	**str;
	t_env	*node;

	i = -1;
	env = NULL;
	while (envp[++i] != NULL)
	{
		str = ft_splitv2(envp[i], '=');
		if (str && str[0] && str[1])
		{
			node = ft_envnew(ft_strdup(str[0]), ft_strdup(str[1]), 1);
			if (node)
				env = ft_envadd_back(env, node);
			else
			{
				ft_free(str);
				ft_envclear(&env, free_string);
				return (NULL);
			}
		}
		ft_free(str);
	}
	return (env);
}

char	**struct_to_env(t_env **env)
{
	int		i;
	char	**str;
	t_env	*current;

	i = 0;
	str = malloc(sizeof(char *) * (ft_envsize(*env) + 1));
	current = *env;
	while (current != NULL)
	{
		current->key = ft_strjoin(current->key, "=");
		str[i] = ft_strjoin(current->key, current->value);
		i++;
		current = current->next;
	}
	str[i] = NULL;
	ft_envclear(env, free_string);
	return (str);
}
