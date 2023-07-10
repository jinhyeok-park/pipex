/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:05:58 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/07/10 13:06:51 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "sys/wait.h"

void	child(char **av, char **envp, int *fd);
char	*cmd_finder(char *av, char **envp);
char	*path_trimer(char **envp);
void	pipex_free(char **input);
void	cmd_exec(char *av, char **envp);
void	parent(char **av, char **envp, int*fd);
void	process_split(char **av, char **envp);

//error
void	input_error_msg(void);
void	pipe_error_msg(void);
void	fork_error_msg(void);
void	cmd_error_msg(void);
void	file_error_msg(void);

#endif