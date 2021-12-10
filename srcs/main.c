/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:38:28 by ajearuth          #+#    #+#             */
/*   Updated: 2021/12/10 14:42:35 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Pour la partie bonus faire une fonction count_arg qui va compter le nomnre de cmd de av[1] a av[len - 1]

int	main(int ac, char **av, const char **envp)
{
	int file1;
	int file2;

	file1 = open(av[1], O_RDONLY);
	file2 = open(av[4],O_CREAT | O_RDWR | O_TRUNC);
	if (file1 == -1 || file2 == -1)
	       return(ft_putstr_ds("Error\n", 2);
	pipex(file1, file2, envp);
	return(0);
}


void	**parse_cmd(char *av)
{
	char **cmd;
	if (cmd == NULL)
		return(NULL);
	cmd = ft_split(av, ' ');
}
