#include "./minishell.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


// int	ft_redirect(t_cmd	*cmd)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (cmd->red[i])
// 	{
// 		printf("----------turn %d----------\n", i);
// 		if (!ft_strcmp(cmd->red[i], ">>"))
// 		{
// 			cmd->fd0 = open(cmd->file[i], O_RDWR | O_CREAT | O_APPEND, 0777);
// 			dup2(cmd->fd0, STDOUT_FILENO);
// 			printf("red: %s\n", cmd->red[i]);
// 			printf("file: %s\n", cmd->file[i]);
// 			printf("append redirection\n");
// 		}
// 		else if (!ft_strcmp(cmd->red[i], ">"))
// 		{
// 			cmd->fd0 = open(cmd->file[i], O_RDWR | O_TRUNC | O_CREAT, 0777);
// 			dup2(cmd->fd0, STDOUT_FILENO);
// 			printf("red: %s\n", cmd->red[i]);
// 			printf("file: %s\n", cmd->file[i]);
// 			printf("right redirection\n");
// 		}
// 		else if (!ft_strcmp(cmd->red[i], "<"))
// 		{
// 			cmd->fd0 = open(cmd->file[i], O_RDONLY, 0777);
// 			if (cmd->fd0 == -1)
// 			{
// 				printf("minishell: %s: %s\n", cmd->file[i], strerror(errno));
// 				i++;
// 				continue;
// 			}
// 			dup2(cmd->fd0, STDIN_FILENO);
// 			printf("red: %s\n", cmd->red[i]);
// 			printf("file: %s\n", cmd->file[i]);
// 			printf("left redirection\n");
// 		}
// 		else if (!ft_strcmp(cmd->red[i], "<<"))
// 		{
// 			dup2(cmd->fd1, STDIN_FILENO);
// 			printf("red: %s\n", cmd->red[i]);
// 			printf("del: %s\n", cmd->delimiter[j++]);
// 			printf("herdoc\n");
// 		}
// 		i++;
// 	}
// 	close(cmd->fd0);
// 	close(cmd->fd1);
// 	return (0);
// }

// int main(int ac, char **av, char **envp) {
// 	(void)av;
// 	(void)ac;
	// int original_stdin = dup(STDIN_FILENO);
	// int original_stdout = dup(STDOUT_FILENO);
	// int		i;
	// int		j;
	// int		k;
	// int		l;
	// int		m;
	// t_cmd	*cmd;
	// char	*line;
	// char	**s;

	// i = 0;
	// cmd = malloc(sizeof(t_cmd));
	// cmd->red = malloc(sizeof(char*) * 5);
	// cmd->file = malloc(sizeof(char*) * 5);
	// cmd->delimiter = malloc(sizeof(char*) * 5);
	// cmd->fd0 = 0;
	// cmd->fd1 = 0;

	// line = readline("Enter command: ");
	// cmd->cmd = ft_split(line, ' ');
	// while(cmd->cmd[i])
	// {
	// 	printf("cmd[%d]: %s\n", i, cmd->cmd[i]);
	// 	i++;
	// }
	// free(line);
	// line = readline("Enter redirection: ");
	// s = ft_split(line, ' ');
	// i = 0;
	// j = 0;
	// k = 0;
	// l = 0;
	// m = 0;
	// while(s[i])
	// {
	// 	// printf("s[%d]: %s\n", i, s[i]);
	// 	if(!ft_strcmp(s[i], "<") || !ft_strcmp(s[i], ">") || !ft_strcmp(s[i], ">>") || !ft_strcmp(s[i], "<<"))
	// 	{
	// 		cmd->red[j] = ft_strdup(s[i]);
	// 		printf("red[%d]: %s\n", j, cmd->red[j]);
	// 		if (!ft_strcmp(s[i], "<<"))
	// 		{
	// 			cmd->delimiter[k] =  ft_strdup(s[i + 1]);
	// 			printf("delimter[%d]: %s\n", k, cmd->delimiter[k]);
	// 			k++;
	// 		}
	// 		else
	// 		{
	// 			cmd->file[l] =  ft_strdup(s[i + 1]);
	// 			printf("file[%d]: %s\n", l, cmd->file[l]);
	// 			l++;
	// 		}
	// 		j++;
	// 	}
	// 	else
	// 	{
	// 		cmd->cmd[m] =  ft_strdup(s[i]);
	// 		printf("cmd[%d]: %s\n", m, cmd->cmd[m]);
	// 		m++;
	// 	}
	// 	i += 2;
	// }
	// cmd->red[j] = NULL;
	// cmd->file[k] = NULL;
	// cmd->delimiter[l] = NULL;
	// free(line);
	// ft_redirect(cmd);
	// dup2(original_stdin, STDIN_FILENO);
	// dup2(original_stdout, STDOUT_FILENO);
	// printf("I/O Rested");
	// ft_free(s);
	// ft_free(cmd->red);
	// ft_free(cmd->file);
	// ft_free(cmd->cmd);
	// free(cmd);
// 	return 0;
// }



// int main(int ac, char **av, char **envp)
// {
// 	(void)av;
// 	(void)ac;

// 	int fd[2][2];
// 	pid_t pid;
// 	int size = 2;
// 	int i = 0;
// 	int j = 0;
// 	char **s;

// 	// Create pipes
// 	while (i < size)
// 	{
// 		if (pipe(fd[i]) == -1)
// 		{
// 			perror("pipe");
// 			exit(EXIT_FAILURE);
// 		}
// 		i++;
// 	}

// 	i = 0;
// 	while (i <= size)
// 	{
// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			perror("fork");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (pid == 0)
// 		{
// 			if (i == 0)
// 			{
// 				printf("First Command\n");
// 				dup2(fd[i][1], STDOUT_FILENO);
// 			}
// 			else if (i == size)
// 			{
// 				printf("Last Command\n");
// 				dup2(fd[i - 1][0], STDIN_FILENO);
// 			}
// 			else
// 			{
// 				printf("Middle Command\n");
// 				dup2(fd[i - 1][0], STDIN_FILENO);
// 				dup2(fd[i][1], STDOUT_FILENO);
// 			}

// 			// Close pipe ends
// 			j = 0;
// 			while (j < size)
// 			{
// 				close(fd[j][0]);
// 				close(fd[j][1]);
// 				j++;
// 			}

// 			// Execute respective command
// 			if (i == 0)
// 			{
// 				s = ft_split("ls -l", ' ');
// 				if (execve("/bin/ls", s, envp) == -1) {
// 					perror("execve");
// 					exit(EXIT_FAILURE);
// 				}
// 			}
// 			else if (i == size)
// 			{
// 				s = ft_split("cat -e", ' ');
// 				if (execve("/bin/cat", s, envp) == -1)
// 				{
// 					perror("execve");
// 					exit(EXIT_FAILURE);
// 				}
// 			}
// 			else
// 			{
// 				s = ft_split("grep libft", ' ');
// 				if (execve("/bin/grep", s, envp) == -1)
// 				{
// 					perror("execve");
// 					exit(EXIT_FAILURE);
// 				}
// 			}
// 		}
// 		i++;
// 	}

// 	// Close pipe ends in the parent process
// 	i = 0;
// 	while (i < size)
// 	{
// 		close(fd[i][0]);
// 		close(fd[i][1]);
// 		i++;
// 	}

// 	// Wait for all child processes to complete
// 	i = 0;
// 	while (i <= size)
// 	{
// 		wait(NULL);
// 		i++;
// 	}

// 	return 0;
// }


// void	readUntilEOF(int fd0, int fd1)
// {
// 	char buffer[1024];
// 	ssize_t bytesRead;
// 	while ((bytesRead = read(fd0, buffer, 1024)) > 0)
// 		write(fd1, buffer, bytesRead);
// 	if (bytesRead == -1)
// 		perror("Error reading file");
// 	close(fd0);
// }

// int main(int ac, char** av, char** envp) {
// 	printf("hello 42\n");
// 	int fd0 = open("file", O_RDONLY);
// 	if (fd0 == -1) {
// 		perror("Error opening file");
// 		return 1;
// 	}
// 	// int fd1 = open("../file1.txt", O_WRONLY | O_CREAT);
// 	// if (fd1 == -1) {
// 	// 	perror("Error opening file");
// 	// 	return 1;
// 	// }
// 	readUntilEOF(fd0, STDIN_FILENO);
// 	printf("future is loading\n");
// 	return 0;
// }
