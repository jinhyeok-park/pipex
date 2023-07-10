/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_control_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:01:49 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/07/10 13:02:22 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

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
