/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:42:05 by ajearuth          #+#    #+#             */
/*   Updated: 2021/12/14 12:19:40 by ajearuth         ###   ########.fr       */
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

char	**find_path(char **envp)
{
	char *find_path;
	char **my_path;

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
	free(find_path);
	return (my_path);
}	

int	make_first_cmd(int fd1, char *cmd1, int *pipefd, char **envp)
{
	char **cmd_av;
	char **my_path;
	char *pathname;
	int i;
	
	dup2(fd1, 0);
	dup2(pipefd[1], 1);
	cmd_av = ft_split(cmd1, ' ');
	my_path = find_path(envp);
	i = 0;

	while(my_path[i])
	{
		pathname = ft_strjoin(my_path[i], cmd1);
		if (access(pathname, F_OK) == 0)
		{
			if (execve(pathname, cmd_av, envp) == -1)
				perror("Execve");
			free(pathname);
			break ;
		}
		free(pathname);
		++i;
	}
	free(cmd_av);	
	free(my_path);
	close(fd1);
	close(pipefd[0]);
	return(0);
}

int	make_second_cmd(int fd2, char *cmd2, int *pipefd, char **envp)
{
	char **cmd_av;
	char **my_path;
	char *pathname;
	int i;
	
	dup2(fd2, 1);
	dup2(pipefd[0], 0);
	cmd_av = ft_split(cmd2, ' ');
	my_path = find_path(envp);
	i = 0;
	while(my_path[i])
	{
		pathname = ft_strjoin(my_path[i], cmd2);
		if(access(pathname, F_OK) == 0)
		{
			if(execve(pathname, cmd_av, envp) == -1)
				perror("Execve");
			free(pathname);
			break ;
		}
		free(pathname);
		++i;
	}
	free(cmd_av);
	free(my_path);
	close(fd2);
	close(pipefd[1]);
	return(0);
}
