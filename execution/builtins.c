/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:36:28 by nettalha          #+#    #+#             */
/*   Updated: 2023/06/15 17:35:21 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit0(char **cmd)
{
	int	n;
	n = 0;
	printf("exit\n");
	if (cmd[1])
		n = ft_atoi(cmd[1]);
	exit(n);
}

void	echo(char **cmd)
{
	int	i;
	int	nflag;

	nflag = 0;
	i = 1;
	// while (cmd[i])
	// {
	// 	printf("str-->|%s|\n", cmd[i++]);
	// }
	// exit(0);
	while (cmd[i] != NULL)
	{
		if (strcmp(cmd[i], "-n") == 0)
			nflag = 1;
		else
		{
			printf("%s", cmd[i]);
			if (cmd[i + 1] != NULL)
				printf(" ");
		}
		i++;
	}
	if (nflag == 0)
		printf("\n");
}

void	cd(char **cmd, t_env *my_envp)
{
	char	*user_dir;
	char	cwd[1024];
	int		r;

	user_dir = ft_strjoin("/Users/", getenv("USER"));
	if (cmd[1] == NULL || !ft_strcmp(cmd[1], "~"))
	{
		ft_upenv("OLDPWD", getcwd(cwd, sizeof(cwd)), my_envp);
		chdir(user_dir);
		ft_upenv("PWD", getcwd(cwd, sizeof(cwd)), my_envp);
	}
	else
	{
		ft_upenv("OLDPWD", getcwd(cwd, sizeof(cwd)), my_envp);
		r = chdir(cmd[1]);
		ft_upenv("PWD", getcwd(cwd, sizeof(cwd)), my_envp);
		if (r != 0)
			printf("cd: %s: No such file or directory\n", cmd[1]);
	}
}

void	pwd(char **cmd)
{
	char cwd[1024];

	if (cmd[1] != NULL)
		printf("pwd: too many arguments\n");
	else
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			printf("%s\n", cwd);
		else
			perror("getcwd() error");
	}
}

void	env(char **cmd, t_env *my_envp)
{
	t_env	*current;

	current = my_envp;
	if (cmd[1] != NULL)
		printf("env takes no arguments\n");
	else
	{
		while (current)
		{
			if (current && (ft_strcmp(current->value, "") || current->is_equ == 1))
				printf("%s=%s\n", current->key, current->value);
			current = current->next;
		}
	}
}

void	ex_env(char **cmd, t_env *my_envp)
{
	t_env	*current;

	current = my_envp;
	if (cmd[1] != NULL)
		printf("env takes no arguments\n");
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

t_env	*export(char **args, t_env *envp)
{
	int	i;
	
	i = 1;
	if (args[1] == NULL)
	{
		char *cmd[] = {"env", NULL};
		ex_env(cmd, envp);
	}
	else
	{
		while(args[i])
			envp = ft_setenv(args[i++], envp);
	}
	return (envp);
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
	else if(!ft_strcmp(cmd->cmd[0], "cd"))
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
