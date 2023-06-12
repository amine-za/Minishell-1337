/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:33:52 by azaghlou          #+#    #+#             */
/*   Updated: 2023/05/27 16:54:32 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **envp)
// {
// 	(void)ac;
// 	(void)av;
// 	t_command   *ll;
// 	char *rd;
// 	env = envp;
// 	while (1)
// 	{
// 		rd = readline("\033[1;35mminishell$ \033[0m");
//     	add_history(rd);
// 		ll = parsing1(rd);

// 		print_ll(ll);
// 		free(rd);
// 	}
// 	return(0);
// }

// int main()
// {
//     char *s = malloc (7);
//     s = "hello_";
//     chrjoin(s, 'a');


// void	redirec_fill(t_cmd *cmd, char **ar)
// {
// 	int i;
// 	char **s;
// 	s = ft_split("ls << ls << kk << cc << nn", ' ');
// 	char *red = ft_strdup(" ");

// 	i = 0;
// 	while (ar[i] && ar[i][0] != '|')
// 	{
// 			red = my_strjoin(my_strjoin(red, " "), ar[i]);
// 		i++;
// 	}
// 	cmd->red = NULL;
// 	cmd->red = ft_split(red, ' ');
// 	printf("red : |%s|\n", red);
// 	i = 0;
// 	while (cmd->red[i])
// 	{
// 		printf("cmd-red: |%s|\n", cmd->red[i]);
// 		i++;
// 	}
// 	ft_free(s);
// }
return 0;
}
