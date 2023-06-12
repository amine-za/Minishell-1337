/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:35:52 by nettalha          #+#    #+#             */
/*   Updated: 2023/06/06 18:12:27 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	free_string(void *str)
{
	free(str);
}

void	ft_free(char **s)
{
	int	i;

	if (!s)
		return;
	else
	{
		i = 0;
		while (s[i])
		{
			free(s[i]);
			i++;
		}
	}
	free(s);
}

char	**check_envp(t_env *env)
{
	char	**paths;

	paths = NULL;
	while (env && env->key != NULL)
	{
		if (!ft_strcmp(env->key, "PATH"))
		{
			if (!ft_strcmp(env->value, "\0"))
			{
				printf("PATH is empty\n");
				return (NULL);
			}
			else
			{
				printf("I found the PATH\n");
				paths = ft_split(env->value, ':');
				return (paths);
			}
		}
		env = env->next;
	}
	printf("PATH was unseted\n");
	return (NULL);
}

char	*getpath(char *cmd, t_env *env, int *error)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	paths = check_envp(env);
	if (!paths)
	{
		printf("minishell: %s: No such file or directory\n", cmd);
		*error = 1;
		return (0);
	}
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if ((access(path, F_OK & R_OK & X_OK)) == 0)
		{
			ft_free(paths);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free(paths);
	*error = 2;
	return (0);
}

char	*quote_handler(char *s, char c)
{
	char	**str;

	str = ft_split(s, c);
	ft_bzero(s, ft_strlen(s));
	while (*str)
	{
		s = ft_strjoin(s, *str);
		str++;
	}
	return (s);
}

// int	ft_isalpha(int c)
// {
// 	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
// 		return 1;
// 	else
// 		return 0;
// }

// int	ft_isalnum(int c)
// {
// 	if (ft_isalpha(c) || (c >= '0' && c <= '9'))
// 		return 1;
// 	else
// 		return 0;
// }

int	check_key(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}


int	ft_error(char *input, char *message, int ret)
{
	input = ft_strjoin(input, ": ");
	ft_putstr_fd("minishell: ", 2);
	if (input != NULL)
		ft_putstr_fd(input, 2);
	ft_putendl_fd(message, 2);
	free(input);
	return (ret);
}
