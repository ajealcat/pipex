/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:41:51 by ajearuth          #+#    #+#             */
/*   Updated: 2021/12/13 15:02:43 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

int	pipex(int file1, int file2, char **av,	char **envp);
int	make_first_cmd(int fd1, char *cmd1, int *pipefd, char **envp);
int	make_second_cmd(int fd2, char *cmd2, int *pipefd, char **envp);

#endif
