/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:37:03 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/07/04 15:11:40 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*list;
	t_list			*backup;
	char			*line;
	int				enter_i;

	if (BUFFER_SIZE < 0 || fd < 0 || read(fd, 0, 0) == -1)
	{
		free_list(&list, fd);
		return (0);
	}
	line = NULL;
	read_checklist(fd, &list);
	enter_i = make_line(list, &line, fd);
	backup = NULL;
	if (enter_i != -1)
		backup = (t_list *)malloc(sizeof(t_list));
	clear_set(enter_i, &list, fd, backup);
	if (!line[0])
	{
		free_list(&list, fd);
		free(line);
		return (NULL);
	}
	return (line);
}

void	clear_set(int enter_index, t_list **list, int fd, t_list *backup)
{
	int		i;
	t_list	*last_node;

	i = 0;
	if (!list)
		return ;
	if (backup)
	{
		last_node = get_last_node(*list, fd, 1);
		backup->data = (char *)malloc(ft_strlen2(last_node->data) - enter_index);
		while (last_node->data[++enter_index])
			backup->data[i++] = last_node->data[enter_index];
		backup->data[i] = '\0';
		backup->next = 0;
		backup->fd = fd;
	}
	free_list(list, fd);
	last_node = get_last_node(*list, fd, 0);
	if (!last_node)
		*list = backup;
	else
		last_node->next = backup;
}

int	line_alloc(char **line, t_list *list, int fd)
{
	int	len;
	int	ret;
	int	i;

	len = 0;
	ret = -1;
	while (list)
	{
		i = 0;
		while (list->fd == fd && list->data[i])
		{
			if (list->data[i] == '\n')
			{
				len++;
				ret = i;
				break ;
			}
			len++;
			i++;
		}
		list = list->next;
	}
	*line = (char *)malloc(len + 1);
	(*line)[len] = '\0';
	return (ret);
}

int	make_line(t_list *list, char **line, int fd)
{
	int	enter_index;
	int	i;
	int	j;

	j = 0;
	enter_index = line_alloc(line, list, fd);
	if (!*line)
		return (-1);
	while (list)
	{
		i = 0;
		while (list->fd == fd && list->data[i])
		{
			if (list->data[i] == '\n')
			{
				(*line)[j] = list->data[i];
				break ;
			}
			(*line)[j] = list->data[i++];
			j++;
		}
		list = list->next;
	}
	return (enter_index);
}

void	add_list(t_list **list, char *buff, ssize_t read_size, int fd)
{
	ssize_t	i;
	t_list	*last_node;
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->next = NULL;
	new_node->fd = fd;
	new_node->data = (char *)malloc(read_size + 1);
	if (!new_node->data)
		return ;
	i = -1;
	while (buff[++i] && i < read_size)
		new_node->data[i] = buff[i];
	new_node->data[i] = '\0';
	if (!*list)
	{
		*list = new_node;
		return ;
	}
	last_node = get_last_node(*list, fd, 0);
	last_node->next = new_node;
}
