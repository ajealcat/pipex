/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:42:05 by ajearuth          #+#    #+#             */
/*   Updated: 2021/12/14 18:13:28 by ajearuth         ###   ########.fr       */
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
	waitpid(child_cmd1, &wstatus, 0);
	waitpid(child_cmd2, &wstatus, 0);
	close(pipefd[0]); // Pas sur de ca
	close (pipefd[1]);  //  :(
	return (0);
}

char	**find_path(char **envp, char *cmd)
{
	char *find_path;
	char **my_path;
	char **cmd_av;
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
	cmd_av = ft_split(cmd, ' ');
	i = 0;
	while (my_path[i])
	{
		my_path[i] = ft_strjoin(my_path[i], "/");
		my_path[i] = ft_strjoin(my_path[i], cmd_av[0]);
		if (access(my_path[i], F_OK == 0))
		{
			free(find_path);
			return(my_path);
		}
		++i;
	}
	free(find_path);
	return (0);
}

int	make_first_cmd(int fd1, char *cmd1, int *pipefd, char **envp)
{
	char **my_path;
	char *pathname;
	
	dup2(fd1, 0);
	dup2(pipefd[1], 1);
	my_path = find_path(envpi, cmd1);
	if (execve(pathname, cmd_av, envp) == -1)
		perror("Execve");
	free(pathname);
	free_all_split(cmd_av, my_path);
	close(fd1);
	close(pipefd[0]);
	return(0);
}

int	make_second_cmd(int fd2, char *cmd2, int *pipefd, char **envp)
{
	char **my_path;
	char *pathname;
	
	dup2(fd2, 1);
	dup2(pipefd[0], 0);
	my_path = find_path(envp, cmd2);
	if(execve(pathname, cmd_av, envp) == -1)
		perror("Execve");
	free(pathname);
	free_all_split(cmd_av, my_path);
	close(fd2);
	close(pipefd[1]);
	return(0);
}
