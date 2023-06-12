#ifndef MINISHELL
# define MINISHELL

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
#include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"
typedef struct vars
{
	int in_sgl;
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
	int				Lpipe;
	int				Rpipe;
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
void	ft_envdelone(char* str, t_env **env);
int		ft_envsize(t_env *env);
t_env	*ft_envlast(t_env *env);
t_env	*ft_envnew(char *key, char *value, int is_equ);
void	ft_upenv(char *key, char *value, t_env *envp);
t_env	*ft_envadd_back(t_env *env, t_env *new_node);
void	ft_envclear(t_env **env, void (*del)(void *));
void	ft_printenv(t_env *env);

int		execute(t_cmd	*cmd, t_env **my_envp);
void	pipes_exec(t_cmd	*cmd, t_env **my_envp);
void	ft_pipe(t_cmd *cmd, t_env **my_envp);
void	ft_signals(void);
int		ft_cmdsize(t_cmd *cmd);
int		redirect(t_cmd	*cmd);
void	ft_herdoc(t_cmd *cmd);
char	*get_valid_path(t_cmd	*cmd, t_env *env, int *error);
char	*getpath(char *cmd, t_env *env, int *error);
int		builtins(t_cmd *cmd, t_env *my_envp);
void	ft_exit0(char **cmd);
int		check_key(char *str);
int		ft_error(char *input, char *message, int ret);
int		builtins_with_path(char **cmd);
void	ft_free(char **s);
void	free_string(void *str);
t_cmd	*parsing1(char *s, t_env *env);
int		syntaxe_err(char **ar);

// amine's functions
char		**chrjoin(char **s, char c, int flag);
char		*rm_quotes(char *s, int flag);
int			count_pipes(char *s);
int			cls_or_opn_qt(int qt);
int			chrch(char *s, char c);
char		*my_strjoin(char *s1, char *s2);
int			my_strcmp(char *s1, char *s2);
void		print_ll(t_cmd *ll);
char		**var_case(char **ar, t_env *env);
char		*dollar_search(char *s);
char		*my_strjoin(char *s1, char *s2);
t_cmd		*add_new(char **ar, t_cmd *prev);
//char		*ft_strdup(char *s1);
//char		*ft_strjoin(char *s1, char *s2);

#endif
