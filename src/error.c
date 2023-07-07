/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:34:18 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/07/05 17:50:51 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	pipe_error_msg(void)
{
	char *str1;
	str1 = "pipe error\n";
	write(2, str1, ft_strlen(str1));
	exit(1);
}

void	fork_error_msg(void)
{
	char *str1;
	str1 = "fork error\n";
	write(2, str1, ft_strlen(str1));
	exit(1);
}

void	input_error_msg(void)
{
	char *str1; 
	char *str2;
	
	str1 = "input error\n";
	str2 = "file1 cmd cmd file2\n";
	write(1, str1, ft_strlen(str1));
	write(2, str2, ft_strlen(str2));
	exit(1);
}

void	cmd_error_msg(void)
{
	char *str1;
	
	str1 = "command not found\n";
	write(1, str1, ft_strlen(str1));
	exit(127);
}

void	file_error_msg(void)
{
	char *str1;
	
	str1 = "no such file or directory\n";
	write(1, str1, ft_strlen(str1));
	exit(1);
}