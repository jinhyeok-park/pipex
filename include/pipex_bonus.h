/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:09:46 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/07/10 15:35:49 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "get_next_line.h"
# include "pipex.h"

void	here_doc_write(char *end, int *fd);
int		file_open(int ac, char **av, int flag);
//process.c
void	first_process(char **av, char **envp, int *fd);
void	second_process(int ac, char **av, char **envp, int *fd);
void	last_process2(int ac, char **av, char **envp, int *fd);
int		is_heredoc(char **av);
//pipe_control.c
int		pipe_control2(int prev_pipe, int *current_pipe);
void	pipe_control(int prev_pipe, int *current_pipe);
void	wait_ids(int ac, char **av);

#endif