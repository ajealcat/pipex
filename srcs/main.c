/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:38:28 by ajearuth          #+#    #+#             */
/*   Updated: 2021/12/14 11:59:13 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int	main(int ac, char **av, char **envp)
{
	int file1;
	int file2;

	file1 = open(av[1], O_RDONLY);
	file2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if(ac)
	{
		if (file1 == -1 || file2 == -1)
		{
			perror("Open");
			return(0);
		}
		pipex(file1, file2, av, envp);
	}
	return(0);
}

