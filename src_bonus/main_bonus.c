/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:08:48 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/07/07 16:21:29 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int main(int ac, char **av, char **envp) {
    // if (ac < 5)
    //     input_error_msg();
    pid_t id;
    int fd[2];
    int file;
    int i;

    pipe(fd);
    i = 2;
    id = fork();
    if (id == 0) {
        // read / cmd start;
        file = open(av[1], O_RDONLY);
        close(fd[0]);
        dup2(file, 0);
        close(file);
        dup2(fd[1], 1);
        close(fd[1]);
        cmd_exec(av[2], envp, 0);
    } else if (id > 0) {
        // 부모 프로세스
        close(fd[1]); // 파이프의 쓰기 쪽 닫음
        int prev_pipe = fd[0]; // 이전 파이프의 읽기 쪽
        for (int i = 3; i < ac - 2; i++) {
            int current_pipe[2];
            if (pipe(current_pipe) == -1) {
                pipe_error_msg();
            }
            pid_t id2 = fork();
            if (id2 == 0) {
                // 자식 프로세스
                dup2(prev_pipe, 0); // 이전 파이프의 읽기 쪽을 stdin으로 리다이렉션
                close(prev_pipe); // 이전 파이프의 읽기 쪽 닫음
                close(current_pipe[0]); // 현재 파이프의 읽기 쪽 닫음
                dup2(current_pipe[1], 1); // 현재 파이프의 쓰기 쪽을 stdout으로 리다이렉션
                close(current_pipe[1]); // 현재 파이프의 쓰기 쪽 닫음
                cmd_exec(av[i], envp, 0);
            } else if (id2 > 0) {
                // 부모 프로세스
                close(prev_pipe); // 이전 파이프의 읽기 쪽 닫음
                close(current_pipe[1]); // 현재 파이프의 쓰기 쪽 닫음
                prev_pipe = current_pipe[0]; // 현재 파이프의 읽기 쪽을 다음 자식 프로세스의 입력으로 설정
            } else {
                fork_error_msg();
                exit(1);
            }
			//close(current_pipe[0]);
        }
        // 마지막 자식 프로세스
        //close(prev_pipe); // 이전 파이프의 읽기 쪽 닫음
        dup2(prev_pipe, 0); // 이전 파이프의 읽기 쪽을 stdin으로 리다이렉션
		close(prev_pipe);
		int as = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
		dup2(as, 1);
		close(as);
		close(fd[1]);
		close(fd[0]);
        cmd_exec(av[ac - 2], envp, 0);
    }

    return 0;
}


// int main(int ac, char **av, char **envp)
// {
// 	if (ac < 5)
// 		input_error_msg();
// 	pid_t id;
// 	int		fd[2];
// 	int		file;
// 	int		i;
	
// 	pipe(fd);
// 	i = 2;
// 	id = fork();
// 	if (id == 0)
// 	{
// 		// read / cmd start;
// 		int	origin_fd;
// 		file = open(av[1], O_RDONLY);
// 		origin_fd = dup(1);
// 		close(fd[0]);
// 		dup2(file, 0);
// 		close(file);
// 		dup2(fd[1], 1);
// 		close(fd[1]);
// 		cmd_exec(av[2], envp, origin_fd);
// 	}
// 	else if (id > 0)
// 	{
// 		// get output data, end next command;
// 		while (++i < ac)
// 		{
// 			int	id2;
// 			int	origin_fd;

// 			id2 = fork();
// 			origin_fd = dup(1);
// 			close(fd[0]);
// 			dup2(fd[1], 1);
// 		}
// 	}
// }

void	process_spliter_bonus(int ac, char **av, char **envp)
{
	pid_t	id;
	int		fd[2];
	int		i;

	if (pipe(fd) == -1)
		pipe_error_msg();
	id = fork();
	i = 1;
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		i = 2;
	if (id == 0)
	{
		if (i == 2)
			here_doc_write(av[2], fd);
		else
			file_process(av, fd);
		exit(0);
	}
	if (id > 0)
	{
		while (++i < ac - 2)
	 		cmd_process(av[i], envp, fd);
		last_process(ac, av, envp);
		waitpid(-1, NULL, 0);
		// char *args[] = {"cat", NULL};
		// execve("/bin/cat", args, NULL);
	}
}

void	file_process(char **av, int *fd)
{
	int	file;

	close(fd[0]);
	file = open(av[1], O_RDONLY);
	if (file == -1)
		file_error_msg();
	dup2(file, 0);
	close(file);
	close(fd[1]);
}

void	last_process(int ac, char **av, char **envp)
{
	int	flag;
	int	file_out;
	int	orign_fd;

	flag = 0;
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		flag = 1;
	if (flag == 1)
		file_out = file_open(ac, av, flag);
	else
		file_out = file_open(ac, av, flag);
	orign_fd = dup(1);
	dup2(file_out, 1);
	cmd_exec(av[ac - 2], envp, orign_fd);
}

void	cmd_process(char *av, char **envp, int *fd)
{
	pid_t	id;
	int		orign_fd;

	orign_fd = dup(1);
	id = fork();
	if (id == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		cmd_exec(av, envp, orign_fd);
	}
	else if (id > 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
	}
	else
		fork_error_msg();
}

void	here_doc_write(char *end, int *fd)
{
	char	*line;

	close(fd[0]);
	while (1)
	{
		line = get_next_line(0);
		if (line == NULL || ft_strncmp(end, line , ft_strlen(line) - 1) == 0)
			break;
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	dup2(fd[1], 1);
	close(fd[1]);
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