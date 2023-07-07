/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:08:48 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/07/07 08:37:23by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int main(int ac, char **av, char **envp) 
{
	pid_t	id;
	pid_t	id2;
	int		fd[2];

	if (ac < 5)
	    input_error_msg();
	pipe(fd);
	id = fork();
	if (id == 0)
		first_process(av, envp, fd);
	else if (id > 0) 
	{
		close(fd[1]); // 파이프의 쓰기 쪽 닫음
		second_process(ac, av, envp, fd);
		id2 = fork();
		if (id2 == 0)
			last_process2(ac, av, envp, fd);
		else if(id2 > 0)
			waitpid(-1, NULL, 0);
		else 
			fork_error_msg();
	}
	else
		fork_error_msg();
}

void	pipe_control(int prev_pipe, int *current_pipe)
{
	dup2(prev_pipe, 0);
	close(prev_pipe);
	close(current_pipe[0]);
	dup2(current_pipe[1], 1);
	close(current_pipe[1]);
}

int	pipe_control2(int prev_pipe, int *current_pipe)
{
	close(prev_pipe);
	close(current_pipe[1]);
	return (current_pipe[0]);
}

void	second_process(int ac, char **av, char **envp, int *fd)
{
	int		prev_pipe;
	int		i;
	int		current_pipe[2];
	int		origin;
	pid_t	id;

	origin = dup(1);
	prev_pipe = fd[0]; // 이전 파이프의 읽기 쪽
	i = 2;
	while (++i < ac - 2)// before last process
	{
		if (pipe(current_pipe) == -1)
			pipe_error_msg();
		id = fork();
		if (id == 0)
		{
			pipe_control(prev_pipe, current_pipe);
			cmd_exec(av[i], envp, origin);
		}
		else if(id > 0)
			prev_pipe = pipe_control2(prev_pipe, current_pipe);
		else
			fork_error_msg();
	}
	dup2(prev_pipe, 0);
	close(prev_pipe);
}

void	last_process2(int ac, char **av, char **envp, int *fd)
{
	int	file_out;
	int	origin_fd;

	origin_fd = dup(1);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		file_out = file_open(ac, av, 1);
	else
		file_out = file_open(ac, av, 0);
	dup2(file_out, 1);
	close(file_out);
	close(fd[1]);
	close(fd[0]);
	cmd_exec(av[ac - 2], envp, origin_fd);
}

void	first_process(char **av, char **envp, int *fd)
{
	int	file;	
	int	origin;
	int	i;

	i = 2;
	origin = dup1(1);
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
	cmd_exec(av[i], envp, origin);
}

void	here_doc_write(char *end, int *fd)
{
	char	*line;

	close(fd[0]);
	while (1)
	{
		line = get_next_line(0);
		if (line == NULL || ft_strncmp(end, line , ft_strlen(line) - 1) == 0)
		{
			dup2(fd[1], 1);
			close(fd[1]);
			exit(0);
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
}

int	file_open(int ac, char **av, int flag)
{
	int	file_out;

	if (flag == 1)
	{
		file_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND ,0644);
		if (file_out == -1)
			file_error_msg();
	}
	else
	{
		file_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC ,0644);
		if (file_out == -1)
			file_error_msg();
	}
	return (file_out);
}
