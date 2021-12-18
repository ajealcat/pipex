/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:38:28 by ajearuth          #+#    #+#             */
/*   Updated: 2021/12/18 16:15:17 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	int	stat;

	stat = 0;

	if (ac == 4 || ac == 5)
	{
		stat = pipex(av, envp);
		if (WIFEXITED(stat))
			return (WEXITSTATUS(stat));
	}
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
