/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:37:18 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/07/03 18:26:05by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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

void    cmd_exec(char *av, char **envp, int origin_fd)
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
			dup2(origin_fd, 1);
			pipex_free(cmd_arr);
			cmd_error_msg();
		}
	}
	if (execve(cmd, cmd_arr, NULL) == -1)
	{
		pipex_free(cmd_arr);
		exit(1);
	}
	pipex_free(cmd_arr);
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
