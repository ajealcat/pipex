/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:38:28 by ajearuth          #+#    #+#             */
/*   Updated: 2021/12/16 15:10:51 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int	main(int ac, char **av, char **envp)
{
	int fd1;
	int fd2;
	
	fd1 = open(av[1], O_RDONLY);
	if (fd1 == -1)
	{
		perror("Open");
		return (1);
	}
	fd2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd2 == -1)
	{
		perror("Open");
		close(fd1);
		return (1);
	}
	if (ac == 4 || ac == 5)
		pipex(av, envp);
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
