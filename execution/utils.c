/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:35:52 by nettalha          #+#    #+#             */
/*   Updated: 2023/06/22 00:14:20 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	i = -1;
	while (paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if ((access(path, F_OK & R_OK & X_OK)) == 0)
			return (ft_free(paths), path);
		free(path);
	}
	*error = 2;
	ft_free(paths);
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
