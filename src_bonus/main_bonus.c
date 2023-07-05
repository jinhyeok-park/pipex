/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:08:48 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/07/05 17:28:27 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int main(int ac, char **av, char **envp)
{
	int	i;
	int	file;
	int	file_out;

	if (ac < 5)
		input_error_msg();
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		i = 2;
		file_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND ,0644);
		here_doc_write(av[2]);
	}
	else
	{
		i = 1;
		file = open(av[1], O_RDONLY);
		file_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC ,0644);
		dup2(file, 0);
	}
	while (++i < ac - 2)
		cmd_process(av[i], envp);
	last_process(ac, av, envp, file_out);
}

void	last_process(int ac, char **av, char **envp, int file_out)
{
	int	orign_fd;

	orign_fd = dup(1);
	dup2(file_out, 1);
	cmd_exec(av[ac - 2], envp, orign_fd);
	wait(NULL);
}

void	cmd_process(char *av, char **envp)
{
	pid_t	id;
	int		fd[2];
	int		orign_fd;

	orign_fd = dup(1);
	if (pipe(fd) == -1)
		pipe_error_msg();
	id = fork();
	if (id == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		cmd_exec(av, envp, orign_fd);
	}
	else if (id > 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
	}
	else
		fork_error_msg();
}

void	here_doc_write(char *end)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		return ;
	while (1)
	{
		line = get_next_line(0);
		if (line == NULL || ft_strncmp(end, line , ft_strlen(line) - 1) == 0)
			break;
		write(fd[1], line, ft_strlen(line));
	}
	close(fd[1]);
	dup2(fd[0], 0);
}

// void	test2(char *end)
// {
// 	int		fd[2];
// 	pid_t	id;
// 	char	*line;

// 	if (pipe(fd) == -1)
// 		return ; 
// 	id = fork();
// 	if (id == 0)
// 	{
// 		close(fd[0]);
// 		while (1)
// 		{
// 			line = get_next_line(0);
// 			if (line == NULL || ft_strncmp(end, line , ft_strlen(line) - 1) == 0)
// 				exit(0);
// 			write(fd[1], line, ft_strlen(line));
// 		}
// 	}
// 	else if (id > 0)
// 	{
// 		close(fd[1]);
// 		dup2(fd[0], 0);
// 		waitpid(id, NULL, 0);
// 	}
// 	else
// 		fork_error_msg();
// }