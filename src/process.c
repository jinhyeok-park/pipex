/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:35:54 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/07/10 12:56:36 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	parent(char **av, char **envp, int *fd)
{
	int	file_out;

	file_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_out == -1)
		file_error_msg();
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	dup2(file_out, 1);
	close(file_out);
	cmd_exec(av[3], envp);
}

void	child(char **av, char **envp, int *fd)
{
	int	file_in;

	file_in = open(av[1], O_RDONLY);
	if (file_in == -1)
		file_error_msg();
	close(fd[0]);
	dup2(file_in, 0);
	close(file_in);
	dup2(fd[1], 1);
	close(fd[1]);
	cmd_exec(av[2], envp);
}
