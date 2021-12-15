/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:38:28 by ajearuth          #+#    #+#             */
/*   Updated: 2021/12/15 12:42:36 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int	main(int ac, char **av, char **envp)
{
	int file1;
	int file2;

	file1 = open(av[1], O_RDONLY);
	if (file1 == -1)
	{
		perror("Open");
		return(0);
	}
	file2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (file2 == -1)
	{
		close(file1);
		perror("Open");
		return(0);
	}
	if(ac == 4 || ac == 5)
		pipex(file1, file2, av, envp);
	close(file1);
	close(file2);
	return(0);
}

void	free_split(char **cmd)
{
	int i;

	i = 0;
	while(cmd[i])
	{
		free(cmd[i]);
		++i;
	}
	free(cmd);
}
