/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:42:05 by ajearuth          #+#    #+#             */
/*   Updated: 2021/12/13 14:09:46 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(int file1, int file2, char **av, char **envp)
{
	int	pipefd[2];
	pid_t	child_cmd1;
	pid_t	child_cmd2;

	pipe(pipefd);
	child_cmd1 = fork();
	if (child_cmd1 < 0)
		return(ft_putstr_fd("Error\n", 2));
	if (child_cmd1 >= 0)
		make_first_cmd(file1, av[3], pipefdi, envp);
	child_cmd2 = fork();
	if (child_cmd2 < 0)
		return(ft_putstr_fd("Error\n", 2));
	if (child_cmd2 >= 0)
		make_second_cmd(file2, av[4], pipefd, envp);
	close(end[0]); // Pas sur de ca
	close (end[1]);  //  :( 
	return (0);
}

int	make_first_cmd(int fd1, char *cmd1, int *pipefd, char **envp)
{
	char **cmd_av;
	char *find_path;
	char **my_path;
	char *pathname;
	int i;
	
	dup2(fd1, 0);
	dup2(pipefd[1], 1);
	cmd_av = ft_split(cmd1, ' ');
	find_path = ft_substr(envp[34], 5, ft_strlen(envp[34]));
	my_path = ft_split(find_path, ':');
	i = 0;

	while(my_path[i])
	{
		pathname = ft_join(my_path[i], cmd1);
		execve(pathname, cmd_av, envp);
		free(pathname);
	}
	close(fd1);
	close(pipefd[0]);
	return(0);
}

int	make_second_cmd(int fd2, char *cmd2, int *pipefd, char **envp)
{
	char **cmd_av;
	char *find_path;
	char **my_path;
	char *pathname;
	int i;
	
	dup2(fd2, 1);
	dup2(pipefd[0], 0);
	cmd_av = ft_split(cmd2, ' ');
	find_path = ft_substr(envp[34], 5, ft_strlen(envp[34]));
	my_path = ft_split(find_path, ':');
	i = 0;

	while(my_path[i])
	{
		pathname = ft_join(my_path[i], cmd2);
		execve(pathname, cmd_av, envp);
		free(pathname);
	}
	close(fd2);
	close(pipefd[0]);
	return(0);

}
