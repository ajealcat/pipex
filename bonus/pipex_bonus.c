/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:31:21 by ajearuth          #+#    #+#             */
/*   Updated: 2021/12/18 15:41:42 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	make_child(char *av, char **envp)
{
	pid_t	child_cmd;
	int		pipefd[2];
	int		status;

	pipe(pipefd)
	child_cmd = fork();
	secure_child(child_cmd);
	if (child_cmd == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], 1) == -1)
		{
			perror("Dup");
			exit(1);
		}
		exec(argv, envp);
	}
	else
	{
		close(pipefd[1]);
		if (dup2(pipefd[0], 0) == -1)
		{
			perror("Dup");
			exit(1);
		}
		waitpid(child_cmd, &status, 0);
	}
	return (status);
}

void	exec(char *argv, char **envp)
{
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (execve(find_path(cmd[0], envp), cmd, envp) == -1)
		perror("Execve");
}

void	here_doc(char *limiter, int ac)
{
	pid_t	reader;
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
	{
		perror("Pipe");
		return (1);
	}
	reader = fork();
	secure_child(reader);
	if (reader == 0)
	{
		close(pipefd[0]);
		while (get_next_line(&line)) //faire le gnl ou mettre celui deja fait en focntion de ce qui est autorise
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(0);
			write(pipefd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(pipefd[1]);
		if (dup2(pipefd[0], 0) == -1)
		{
			perror("Dup");
			exit(1);
		}
		wait(NULL);
	}
}
