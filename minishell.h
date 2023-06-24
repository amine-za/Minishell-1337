/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 14:50:18 by azaghlou          #+#    #+#             */
/*   Updated: 2023/06/24 20:41:44 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

typedef struct g_glb
{
	int				status;
	int				exit_status;
	int				o_stdin;
	int				o_stdout;
	sig_atomic_t	sigint;
}	t_glb;

extern t_glb	g_glb;

typedef struct vars
{
	int	in_sgl;
	int	in_dbl;
}	t_inf;

typedef struct s_env
{
	struct s_env	*prev;
	char			*key;
	char			*value;
	int				is_equ;
	struct s_env	*next;
}t_env;

typedef struct s_cmd
{
	char			**cmd;
	int				fd0;
	int				fd1;
	int				lpipe;
	int				rpipe;
	int				err;
	char			**red;
	char			**file;
	char			*heredoc_file;
	char			**delimiter;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

void	rl_replace_line(const char *text, int clear_undo);
char	**struct_to_env(t_env **env);
t_env	*env_to_struct(char **envp);
t_env	*ft_setenv(char *str, t_env *envp);
void	ft_unsetenv(char *str, t_env *envp);
void	ft_envdelone(char *str, t_env **env);
int		ft_envsize(t_env *env);
t_env	*ft_envlast(t_env *env);
t_env	*ft_envnew(char *key, char *value, int is_equ);
void	ft_upenv(char *key, char *value, t_env *envp);
t_env	*ft_envadd_back(t_env *env, t_env *new_node);
void	ft_envclear(t_env **env, void (*del)(void *));
void	ft_printenv(t_env *env);

t_cmd	*parse(t_cmd *cmd, t_env *my_envp, char *line);
int		execute(t_cmd	*cmd, t_env **my_envp);
void	pipes_exec(t_cmd	*cmd, t_env **my_envp);
void	ft_pipe(t_cmd *cmd, t_env **my_envp);
void	ft_signals(void);
int		ft_cmdsize(t_cmd *cmd);
int		redirect(t_cmd	*cmd);
int		check_red(t_cmd *cmd, int n);
void	ft_herdoc(t_cmd *cmd, int n);
void	heredoc1(t_cmd *cmd, int i);
void	check_herdoc(t_cmd *cmd);
char	*get_valid_path(t_cmd	*cmd, t_env *env, int *error);
char	*getpath(char *cmd, t_env *env, int *error);
int		check_key(char *str);
void	ft_error(char *input, char *message, int errnb);
void	ft_free(char **s);
void	free_string(void *str);
t_cmd	*parsing1(char *s, t_env *env);
int		syntaxe_err(char **ar);
void	herdoc_signals(void);
void	free_ll(t_cmd *cmd);
void	save_fds(int ac, char **av);
void	backup_fds(void);
void	backup_free(t_cmd *cmd, char *line);
void	handle_exit(char *line);
void	exe_sighandler(int sig);
void	ft_exsignals(void);
// builtins-utils
int		builtins(t_cmd *cmd, t_env *my_envp);
t_env	*export(char **args, t_env *envp);
void	unset(char **cmd, t_env *my_envp);
void	echo(char **cmd);
void	cd(char **cmd, t_env *my_envp);
void	pwd(char **cmd);
void	env(char **cmd, t_env *my_envp);
void	ft_exit0(char **cmd);
void	ex_env(char **cmd, t_env *my_envp);
//pipes_utils
void	fds_opertions(int **fd, pid_t	*pid, int size, int n);
void	dup_fds(int **fd, int i, int size);
void	free_fds(int **fd, int size);
void	wait_pids(pid_t	*pid, int size);
void	close_fds(int **fd, int size);
void	pipe_fds(int **fd, int size);
int		ft_cmdsize(t_cmd *cmd);
// amine's functions
char	**chrjoin(char **s, char c, int flag);
char	*rm_quotes(char *s);
int		count_pipes(char *s);
int		cls_or_opn_qt(int qt);
int		chrch(char *s, char c);
char	*my_strjoin(char *s1, char *s2);
int		my_strcmp(char *s1, char *s2);
void	print_ll(t_cmd *ll);
char	**var_case(char **ar, t_env *env);
char	*dollar_search(char *s);
char	*my_strjoin(char *s1, char *s2);
t_cmd	*add_new(char **ar, t_cmd *prev);
char	*env_chck(char *s, int indc, t_env *p);
void	env_chck_norm(char *f_part, char *s, int i, int indc);
int		dollar_count(char *s);
char	*search_for_var(t_env *p, char *var_name, char *f_part);
char	*variable_name(char *s, int flag);
char	**check_and_token(char *s, t_env *env);
char	**case_of_red_or_pipe(char **ar, char *s, int *i);
char	**case_of_sgl_quote(char **ar, char *s, int *i, t_inf *p);
char	**case_of_dbl_quotes(char **ar, char *s, int *i, t_inf *p);
void	case_of_space(int *i);
char	**els(char **ar, char *s, int *i, t_inf p);
int		if_append_or_herdoc(char *s, int *i, t_inf *p);
int		if_pipe_or_red( char *s, int *i, t_inf *p);
char	**case_of_append_or_herdoc(char **ar, char *s, int *i);
int		t_glbl_var_fct(int j, int flag);
t_inf	quotes_inf_for_var(t_inf p, char *ar, int i);
int		point_in_dollar(char *s, int indc);
char	*number_expen_case(char *f_part, char *var_name);
#endif
