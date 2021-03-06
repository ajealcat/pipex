/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:31:21 by ajearuth          #+#    #+#             */
/*   Updated: 2021/12/21 12:15:39 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	make_child(char *av, char **envp)
{
	pid_t	child_cmd;
	int		pipefd[2];
	int		status;

	if (pipe(pipefd) == -1)
		error_pipe();
	child_cmd = fork();
	secure_child(child_cmd);
	if (child_cmd == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], 1) == -1)
			error();
		exec(av, envp);
	}
	else
	{
		waitpid(child_cmd, &status, 0);
		close(pipefd[1]);
		if (dup2(pipefd[0], 0) == -1)
			error();
	}
	return (status);
}

int	make_last_child(char **av, int ac, char **envp)
{
	pid_t	last_child;
	int		pipefd[2];
	int		status;

	if (pipe(pipefd) == -1)
		error_pipe();
	last_child = fork();
	secure_child(last_child);
	if (last_child == 0)
	{
		close(pipefd[0]);
		exec(av[ac - 2], envp);
	}
	else
	{
		waitpid(last_child, &status, 0);
		close(pipefd[1]);
	}
	return (status);
}

void	error(void)
{
	perror("Dup");
	exit(1);
}

void	exec(char *av, char **envp)
{
	char	**cmd;

	cmd = ft_split(av, ' ');
	if (execve(find_path(cmd[0], envp), cmd, envp) == -1)
		perror("Execve");
}
