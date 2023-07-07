/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:42:28 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/07/07 11:10:00 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int main(int ac, char **av, char **envp)
{
	if (ac != 5)
 		input_error_msg();
	process_split(av, envp);
}

void	process_split(char **av, char **envp)
{
	pid_t	id;
	pid_t	id2;
	int		fd[2];

	if (pipe(fd) == -1)
		pipe_error_msg();
	id = fork();
	if (id == 0)
		child(av, envp, fd);
	else if (id > 0)
	{
		id2 = fork();
		if (id2 == 0)
			parent(av, envp, fd);
		else if (id2 > 0)
		{
			close(fd[0]);
			close(fd[1]);
			waitpid(id2, NULL, 0);
			waitpid(id, NULL, 0);
		}
	}
	else
		fork_error_msg();
}
