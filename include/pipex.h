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
void    cmd_exec(char *av, char **envp);
void	parent(char **av, char **envp, int *fd);

#endif