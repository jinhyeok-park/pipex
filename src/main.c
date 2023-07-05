#include "../include/pipex.h"


int main(int ac, char **av, char **envp)
{
	int     fd[2];
	int		status;
	pid_t   id;

	if (ac != 5)
		input_error_msg();
	if (pipe(fd) == -1)
		pipe_error_msg();
	id = fork();
	if (id == 0)
		child(av, envp, fd);
	else if (id > 0)
	{
		waitpid(id, &status, WNOHANG);
		if (!WIFEXITED(status))
			exit(WEXITSTATUS(status));
		parent(av, envp, fd);
	}
	else
		fork_error_msg();
}
