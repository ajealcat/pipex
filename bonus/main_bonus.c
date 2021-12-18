/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:28:12 by ajearuth          #+#    #+#             */
/*   Updated: 2021/12/18 14:28:12 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	int	i;
	int stat;
	int	file_in;
	int	file_out;

	stat = 0;
	if (ac >= 5)
	{
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
		{
			i = 3;
			file_out = open_file(av[ac - 1], 0);
			here_doc(av[2], ac);
		}
		else
		{
			i = 2;
			file_out = open_file(av[ac - 1], 1);
			file_in = open_file(av[1], 2);
			if (dup2(file_in, 0) == -1)
			{
				perror("Dup");
				exit(1);
			}
		}
		while (i < ac - 2)
		{
			stat = make_child(av[i++], envp);
			if (WIFEXITED(stat))
				return (WEXITSTATUS(stat));
		}
		if (dup2(file_out, 1) == -1)
		{
			perror("Dup");
			exit(1);
		}
		if (exec(av[ac - 2], envp) == -1)
				perror("Execve");
	}
	return(127);
}

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
	{
		perror("Open");
		exit(1);
	}
	return (file);
}
