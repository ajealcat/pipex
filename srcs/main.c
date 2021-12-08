/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:38:28 by ajearuth          #+#    #+#             */
/*   Updated: 2021/12/08 17:58:39 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Pour la partie bonus faire une fonction count_arg qui va compter le nomnre de cmd de av[1] a av[len - 1]

int	read_cmd(int cmd)
{
	
}

int	exec()
{
}

int	main(int ac, char **av)
{
	int file1;
	int file2;

	file1 = open(av[1], O_RDONLY);
	file2 = open(av[4], 0_RDWR | O_TRUNC | O_CREAT);
	if (file1 == -1 || file2 == -1)
	       return(error());


}
