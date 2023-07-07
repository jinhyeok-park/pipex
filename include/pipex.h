# ifndef PIPEX_H
#define PIPEX_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "../libft/libft.h"
#include "sys/wait.h"

void	child(char **av, char **envp, int *fd);
char	*cmd_finder(char *av, char **envp);
char	*path_trimer(char **envp);
void	pipex_free(char **input);
void    cmd_exec(char *av, char **envp, int origin_fd);
void	parent(char **av, char **envp, int*fd);
//void	process_spliter(char **av, char **envp);
void	process_split(char **av, char **envp);

//error
void	input_error_msg(void);
void	pipe_error_msg(void);
void	fork_error_msg(void);
void	cmd_error_msg(void);
void	file_error_msg(void);

#endif