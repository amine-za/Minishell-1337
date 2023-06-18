/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:35:52 by nettalha          #+#    #+#             */
/*   Updated: 2023/06/18 22:41:51 by nettalha         ###   ########.fr       */
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
		return ;
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
		ft_error(cmd, "No such file or directory", 1);
		*error = 1;
		exit(g_glb.exit_status);
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

char	*get_valid_path(t_cmd	*cmd, t_env *env, int *error)
{
	char	*valid_path;

	valid_path = NULL;
	if (!cmd->cmd[0])
		return (NULL);
	if (ft_strchr(cmd->cmd[0], '/') && !access(cmd->cmd[0], F_OK | R_OK | X_OK))
		valid_path = ft_strdup(cmd->cmd[0]);
	else if (ft_strnstr(cmd->cmd[0], "./", ft_strlen(cmd->cmd[0])))
	{
		if (!access(cmd->cmd[0], F_OK | R_OK | X_OK))
			valid_path = ft_strdup(cmd->cmd[0]);
		else
		{
			ft_error(cmd->cmd[0], strerror(errno), 126);
			exit(g_glb.exit_status);
		}
	}
	else
	{
		valid_path = getpath(cmd->cmd[0], env, error);
	}
	return (valid_path);
}

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

void	ft_error(char *input, char *message, int errnb)
{
	input = ft_strjoin(input, ": ");
	ft_putstr_fd("minishell: ", 2);
	if (input != NULL)
		ft_putstr_fd(input, 2);
	ft_putendl_fd(message, 2);
	free(input);
	g_glb.exit_status = errnb;
	printf(">>exit_status>> %d\n", g_glb.exit_status);
}
