/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:36:28 by nettalha          #+#    #+#             */
/*   Updated: 2023/06/24 21:29:34 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit0(char **cmd)
{
	int	n;

	n = g_glb.exit_status;
	printf("exit\n");
	if (cmd[1])
		n = ft_atoi(cmd[1]);
	exit(n);
}

void	ex_env(char **cmd, t_env *my_envp)
{
	t_env	*current;

	current = my_envp;
	if (cmd[1] != NULL)
		ft_putstr_fd("env takes no arguments\n", 2);
	else
	{
		while (current)
		{
			if (!ft_strcmp(current->value, "") && current->is_equ == 0)
				printf("declare -x %s%s\n", current->key, current->value);
			else
				printf("declare -x %s=\"%s\"\n", current->key, current->value);
					current = current->next;
		}
	}
}

void	unset(char **cmd, t_env *my_envp)
{
	int	i;

	i = 1;
	while (cmd[i])
		ft_envdelone(cmd[i++], &my_envp);
}

int	builtins(t_cmd *cmd, t_env *my_envp)
{
	if (!cmd->cmd || !cmd->cmd[0])
		return (0);
	if (!ft_strcmp(cmd->cmd[0], "echo"))
		return (echo(cmd->cmd), 1);
	else if (!ft_strcmp(cmd->cmd[0], "cd"))
		return (cd(cmd->cmd, my_envp), 1);
	else if (!ft_strcmp(cmd->cmd[0], "pwd"))
		return (pwd(cmd->cmd), 1);
	else if (!ft_strcmp(cmd->cmd[0], "env"))
		return (env(cmd->cmd, my_envp), 1);
	else if (!ft_strcmp(cmd->cmd[0], "export"))
		return (export(cmd->cmd, my_envp), 1);
	else if (!ft_strcmp(cmd->cmd[0], "unset"))
		return (unset(cmd->cmd, my_envp), 1);
	else if (!ft_strcmp(cmd->cmd[0], "exit"))
	{
		ft_exit0(cmd->cmd);
		return (1);
	}
	return (0);
}

// int	builtins_with_path(char **cmd)
// {
// 	if (!ft_strcmp(cmd[0], "/bin/echo"))
// 		return (1);
// 	else if(!ft_strcmp(cmd[0], "/bin/cd"))
// 		return (1);
// 	else if (!ft_strcmp(cmd[0], "/bin/pwd"))
// 		return (1);
// 	return (0);
// }
