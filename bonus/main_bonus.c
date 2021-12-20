/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:28:12 by ajearuth          #+#    #+#             */
/*   Updated: 2021/12/20 16:58:13 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **envp)
{
	int	i;
	int	file_in;
	int	file_out;

	if (ac >= 5)
	{
		file_out = open_file(av[ac - 1], 1);
		file_in = open_file(av[1], 2);
		if (dup2(file_in, 0) == -1)
		{
			perror("Dup");
			exit(1);
		}
		i = 2;
		while (i < (ac - 2))
			make_child(av[i++], envp);
		if (dup2(file_out, 1) == -1)
		{
			perror("Dup");
			exit(1);
		}
		exec(av[ac - 2], envp);
	}
	return (127);
}

int	open_file(char *av, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(av, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(av, O_RDONLY, 0777);
	if (file == -1)
	{
		perror("Open");
		exit(1);
	}
	return (file);
}
