/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:32:49 by ajearuth          #+#    #+#             */
/*   Updated: 2021/12/18 16:15:06 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h> 
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

char	*find_path(char *cmd, char **envp);
char	*parse_path(char **envp);
int		secure_child(pid_t child_cmd);
int		make_child(char *av, char **envp);
int		open_file(char *argv, int i);
void	exec(char *argv, char **envp);
void	here_doc(char *limiter, int ac);


#endif
