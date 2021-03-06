/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:38:28 by ajearuth          #+#    #+#             */
/*   Updated: 2021/12/21 12:14:15 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	int	stat;

	stat = 0;
	if (ac == 5)
	{
		stat = pipex(av, envp);
		if (WIFEXITED(stat))
			return (WEXITSTATUS(stat));
	}
	if (ac > 5 || ac < 5)
		ft_putstr_fd("Try this way : ./pipex file1 <cmd1> <cmd2> file2\n", 1);
	return (127);
}

void	free_split(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		++i;
	}
	free(cmd);
}

void	error_pipe(void)
{
	perror("Pipe");
	exit(1);
}

int	secure_child(pid_t child_cmd)
{
	if (child_cmd < 0)
	{
		perror("Fork");
		return (1);
	}
	return (0);
}

char	*parse_path(char **envp)
{
	char	*find_path;

	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			find_path = ft_substr(*envp, 5, ft_strlen(*envp));
			break ;
		}
		++envp;
	}
	return (find_path);
}
