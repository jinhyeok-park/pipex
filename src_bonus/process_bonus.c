/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:02:43 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/07/10 15:13:31 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	second_process(int ac, char **av, char **envp, int *fd)
{
	int		prev_pipe;
	int		i;
	int		current_pipe[2];
	pid_t	id;

	prev_pipe = fd[0];
	i = is_heredoc(av);
	while (++i < ac - 2)
	{
		if (pipe(current_pipe) == -1)
			pipe_error_msg();
		id = fork();
		if (id == 0)
		{
			pipe_control(prev_pipe, current_pipe);
			cmd_exec(av[i], envp);
		}
		else if (id > 0)
			prev_pipe = pipe_control2(prev_pipe, current_pipe);
		else
			fork_error_msg();
	}
	dup2(prev_pipe, 0);
	close(prev_pipe);
}

int	is_heredoc(char **av)
{
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		return (3);
	return (2);
}

void	last_process2(int ac, char **av, char **envp, int *fd)
{
	int	file_out;

	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		file_out = file_open(ac, av, 1);
	else
		file_out = file_open(ac, av, 0);
	dup2(file_out, 1);
	close(file_out);
	close(fd[1]);
	close(fd[0]);
	cmd_exec(av[ac - 2], envp);
}

void	first_process(char **av, char **envp, int *fd)
{
	int	file;	
	int	i;

	i = 2;
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		i = 3;
		here_doc_write(av[2], fd);
	}
	else
	{
		file = open(av[1], O_RDONLY);
		if (file == -1)
			file_error_msg();
		close(fd[0]);
		dup2(file, 0);
		close(file);
		dup2(fd[1], 1);
		close(fd[1]);
	}
	cmd_exec(av[i], envp);
}
