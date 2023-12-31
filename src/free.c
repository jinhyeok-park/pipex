/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:37:49 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/07/10 12:55:16 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	pipex_free(char **input)
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
