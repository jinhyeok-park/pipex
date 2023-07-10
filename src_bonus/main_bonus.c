/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:08:48 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/07/10 15:39:18 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	main(int ac, char **av, char **envp)
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
		close(fd[1]);
		second_process(ac, av, envp, fd);
		id2 = fork();
		if (id2 == 0)
			last_process2(ac, av, envp, fd);
		else if (id2 > 0)
			wait_ids(ac, av);
		else
			fork_error_msg();
	}
	else
		fork_error_msg();
}

void	wait_ids(int ac, char **av)
{
	int	i;

	i = 2;
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		i = 3;
	while (++i < ac)
		waitpid(-1, NULL, 0);
}

void	here_doc_write(char *end, int *fd)
{
	char	*line;

	close(fd[0]);
	while (1)
	{
		line = get_next_line(0);
		if (line == NULL || ft_strncmp(end, line, ft_strlen(line) - 1) == 0)
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
		file_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (file_out == -1)
			file_error_msg();
	}
	else
	{
		file_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file_out == -1)
			file_error_msg();
	}
	return (file_out);
}
