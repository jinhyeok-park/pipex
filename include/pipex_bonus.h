/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:09:46 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/07/07 09:49:31 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX_BONUS_H
#define PIPEX_BONUS_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "../libft/libft.h"
#include "sys/wait.h"
#include "get_next_line.h"
#include "pipex.h"


void	here_doc_write(char *end, int *fd);
void	cmd_process(char *av, char **envp, int *fd);
void	last_process(int ac, char **av, char **envp);
int		file_open(int ac, char **av, int flag);
void	process_spliter_bonus(int ac, char **av, char **envp);


void	first_process(char **av, char **envp, int *fd);
void	file_process(char **av, int *fd);
void	second_process(int ac, char **av, char **envp, int *fd);
int	pipe_control2(int prev_pipe, int *current_pipe);
void	pipe_control(int prev_pipe, int *current_pipe);
void	last_process2(int ac, char **av, char **envp, int *fd);
//gnl

# endif