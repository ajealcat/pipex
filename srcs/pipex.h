/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:41:51 by ajearuth          #+#    #+#             */
/*   Updated: 2021/12/15 15:42:23 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

//(define stdin, stdout = 1 ou 0)


int	pipex(char **av, char **envp);
int	make_first_cmd(char *file1, char *cmd1, int *pipefd, char **envp);
int	make_second_cmd(char *file2, char *cmd2, int *pipefd, char **envp);
char	*find_path(char **envp, char **cmd_av);
void    free_split(char **cmd);

#endif
