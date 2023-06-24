/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 11:46:17 by nettalha          #+#    #+#             */
/*   Updated: 2023/06/24 19:34:40 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*export(char **args, t_env *envp)
{
	char	*cmd[2];
	int		i;

	i = 1;
	if (args[1] == NULL)
	{
		cmd[0] = "env";
		cmd[1] = NULL;
		ex_env(cmd, envp);
	}
	else
	{
		while (args[i])
			envp = ft_setenv(args[i++], envp);
	}
	return (envp);
}

void	echo(char **cmd)
{
	int	i;
	int	nflag;

	nflag = 0;
	i = 1;
	while (cmd[i] != NULL)
	{
		if (ft_strcmp(cmd[i], "-n") == 0)
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
			ft_error(cmd[1], "No such file or directory", 1);
	}
	free(user_dir);
}

void	pwd(char **cmd)
{
	char	cwd[1024];

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
			if (current
				&& (ft_strcmp(current->value, "") || current->is_equ == 1))
				printf("%s=%s\n", current->key, current->value);
			current = current->next;
		}
	}
}
