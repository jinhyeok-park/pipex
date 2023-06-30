#include "pipex.h"

void    printer(char **in, int ac);

int main(int ac, char **av, char **envp)
{
	int     fd[2];
	int		status;
	pid_t   id;

	if (ac != 5)
	{
	    //error
	    return (0);
	}
	if (pipe(fd) == -1)
	{
		//pipe error
		return (0);
	}
	id = fork();
	if (id == 0)
		child(av, envp, fd);
	else if (id > 0)
	{
		wait(&status);
		parent(av, envp, fd);
	}
	else
	{
		//fork_fail;
	}
}

void    printer(char **in, int ac)
{
	if (ac == 0)
	{
		for (int i = 0 ; in[i] ; i++)
			printf("%s\n", in[i]);
	}
	else
	{
		for (int i = 0 ; i < ac ; i++)
		{
			printf("%s\n", in[i]);
		}
	}
}

void	parent(char **av, char **envp, int *fd)
{
	int	file_out;

	file_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC ,0777);
	if (file_out == -1)
		return ;
	dup2(file_out, 1);
	dup2(fd[0], 0);
	close(fd[1]);
    cmd_exec(av[3], envp);
}

void    child(char **av, char **envp, int *fd)
{
    int file_in;

    file_in = open(av[1], O_RDONLY);
	if (file_in == -1)
		return ;
    dup2(file_in, 0);
    dup2(fd[1], 1);
    close(fd[0]);
    cmd_exec(av[2], envp);
}

char    *cmd_finder(char *cmd, char **envp)
{
	int		i;
	char    **envp_path;
	char	*slash;
	char	*stream;

	i = -1;
	envp_path = ft_split(path_trimer(envp), ':');
	while (envp_path[++i])
	{
		slash = ft_strjoin(envp_path[i], "/");
		stream = ft_strjoin(slash, cmd);
		free(slash);
		slash = NULL;
		if (access(stream, F_OK) == 0)
		{
			pipex_free(envp_path);
			return (stream);
		}
		free(stream);
		stream = NULL;
	}
	free(stream);
	stream = NULL;
	pipex_free(envp_path);
	return (0);
}

void    pipex_free(char **input)
{
	int	i;

	i = -1;
	if (input)
	{
		while (input[++i])
			free(input[i]);
		free(input);
	}
}

char    *path_trimer(char **envp)
{
	int     i;
	char    *dup;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			dup = ft_strdup(envp[i] + 5);
			return (dup);
		}
	}
	return (0);
}

void    cmd_exec(char *av, char **envp)
{
	char	*cmd;
	char	**cmd_arr;

	cmd_arr = ft_split(av, ' ');
	if (access(cmd_arr[0], F_OK) == 0)
		cmd = av;
	else
	{
		cmd = cmd_finder(cmd_arr[0], envp);
		if (!cmd)
		{
			//error;
		}
	}
	if (execve(cmd, cmd_arr, NULL) == -1)
	{
		pipex_free(cmd_arr);
		return ;
	}
	pipex_free(cmd_arr);
}