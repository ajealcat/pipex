/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 13:48:42 by ajearuth          #+#    #+#             */
/*   Updated: 2021/12/21 12:12:09 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*find_path(char *cmd, char **envp)
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
		my_path[i] = ft_strjoin(my_path[i], cmd);
		if (access(my_path[i], X_OK) == 0)
		{
			free(find_path);
			return (my_path[i]);
		}
		i++;
	}
	free_split(my_path);
	free(find_path);
	return (0);
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

void	error_pipe(void)
{
	perror("Pipe");
	exit (1);
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
