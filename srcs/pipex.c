/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:42:05 by ajearuth          #+#    #+#             */
/*   Updated: 2021/12/21 12:14:53 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(char **av, char **envp)
{
	int		pipefd[2];
	int		status;
	pid_t	child_cmd1;
	pid_t	child_cmd2;

	if (pipe(pipefd) == -1)
		error_pipe();
	child_cmd1 = fork();
	secure_child(child_cmd1);
	if (child_cmd1 == 0)
		make_first_cmd(av[1], av[2], pipefd, envp);
	child_cmd2 = fork();
	secure_child(child_cmd2);
	if (child_cmd2 == 0)
		make_second_cmd(av[4], av[3], pipefd, envp);
	close(pipefd[0]);
	close (pipefd[1]);
	waitpid(child_cmd1, &status, 0);
	waitpid(child_cmd2, &status, 0);
	return (status);
}

char	*find_path(char **envp, char **cmd_av)
{
	char	*find_path;
	char	**my_path;
	int		i;

	find_path = parse_path(envp);
	my_path = ft_split(find_path, ':');
	i = 0;
	while (my_path[i])
	{
		my_path[i] = ft_strjoin(my_path[i], "/");
		my_path[i] = ft_strjoin(my_path[i], cmd_av[0]);
		if (access(my_path[i], X_OK) == 0)
		{
			if (execve(my_path[i], cmd_av, envp) == -1)
				perror("Execve");
			free(find_path);
			return (my_path[i]);
		}
		i++;
	}
	free_split(my_path);
	free(find_path);
	return (0);
}

int	make_first_cmd(char *file1, char *cmd1, int *pipefd, char **envp)
{
	char	**cmd_av;
	int		fd1;

	fd1 = open(file1, O_RDONLY);
	if (fd1 == -1)
	{
		perror("Open");
		exit(1);
	}	
	cmd_av = ft_split(cmd1, ' ');
	if (dup2(fd1, 0) == -1)
	{
		perror("Dup");
		exit(1);
	}
	if (dup2(pipefd[1], 1) == -1)
	{
		perror("Dup");
		exit(1);
	}
	close(pipefd[0]);
	find_path(envp, cmd_av);
	free_split(cmd_av);
	return (0);
}

int	make_second_cmd(char *file2, char *cmd2, int *pipefd, char **envp)
{
	int		fd2;
	char	**cmd_av;

	fd2 = open(file2, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd2 == -1)
	{
		perror("Open");
		exit(1);
	}
	cmd_av = ft_split(cmd2, ' ');
	if (dup2(fd2, 1) == -1)
	{
		perror("Dup");
		exit(1);
	}
	if (dup2(pipefd[0], 0) == -1)
	{
		perror("Dup");
		exit(1);
	}
	close(pipefd[1]);
	find_path(envp, cmd_av);
	free_split(cmd_av);
	return (0);
}
