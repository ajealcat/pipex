/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:42:05 by ajearuth          #+#    #+#             */
/*   Updated: 2021/12/15 12:36:08 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(int file1, int file2, char **av, char **envp)
{
	int	pipefd[2];
	int	wstatus;
	pid_t	child_cmd1;
	pid_t	child_cmd2;

	pipe(pipefd);
	child_cmd1 = fork();
	if (child_cmd1 < 0)
	{
		perror("Fork");
		return (0);
	}
	if (child_cmd1 >= 0)
		make_first_cmd(file1, av[2], pipefd, envp);
	child_cmd2 = fork();
	if (child_cmd2 < 0)
	{
		perror("Fork");
		return (0);
	}
	if (child_cmd2 >= 0)
		make_second_cmd(file2, av[3], pipefd, envp);
	close(pipefd[0]);
	close (pipefd[1]);
	waitpid(child_cmd1, &wstatus, 0);
	waitpid(child_cmd2, &wstatus, 0);
	return (0);
}

char	*find_path(char **envp, char **cmd_av)
{
	char *find_path;
	char **my_path;
	int	i;

	while(*envp)
	{
		if(ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			find_path = ft_substr(*envp, 5, ft_strlen(*envp));
			break ;
		}
		++envp;
	}
	my_path = ft_split(find_path, ':');
	i = 0;
	while (my_path[i])
	{
		my_path[i] = ft_strjoin(my_path[i], "/");
		my_path[i] = ft_strjoin(my_path[i], cmd_av[0]);
		if (access(my_path[i], X_OK) == 0)
		{
			free(find_path);
			return(my_path[i]);
		}
		++i;
	}
	free(find_path);
	return (0);
}


int	make_first_cmd(int fd1, char *cmd1, int *pipefd, char **envp)
{
	char *pathname;
	char **cmd_av;

	dup2(fd1, 0);
	dup2(pipefd[1], 1);
	cmd_av = ft_split(cmd1, ' ');
	pathname = find_path(envp, cmd_av);
	close(pipefd[0]);
	execve(pathname, cmd_av, envp);
	perror("Execve");
	free(pathname);
	free_split(cmd_av);
	return(0);
}

int	make_second_cmd(int fd2, char *cmd2, int *pipefd, char **envp)
{
	char **cmd_av;
	char *pathname;
	
	dup2(fd2, 1);
	dup2(pipefd[0], 0);
	cmd_av = ft_split(cmd2, ' ');
	pathname = find_path(envp, cmd_av);
	close(pipefd[1]);
	execve(pathname, cmd_av, envp);
	perror("Execve");
	free(pathname);
	free_split(cmd_av);
	return(0);
}
