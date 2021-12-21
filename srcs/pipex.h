/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:41:51 by ajearuth          #+#    #+#             */
/*   Updated: 2021/12/21 12:16:28 by ajearuth         ###   ########.fr       */
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

int		pipex(char **av, char **envp);
int		make_first_cmd(char *file1, char *cmd1, int *pipefd, char **envp);
int		make_second_cmd(char *file2, char *cmd2, int *pipefd, char **envp);
int		secure_child(pid_t child_cmd);
char	*find_path(char **envp, char **cmd_av);
char	*parse_path(char **envp);
void	free_split(char **cmd);
void	error_pipe(void);

#endif
