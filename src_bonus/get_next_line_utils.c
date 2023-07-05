/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:48:39 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/07/04 15:11:07 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

size_t	ft_strlen2(char *str)
{
	size_t	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	free_list(t_list **list, int fd)
{
	t_list	*temp;
	t_list	*head;

	head = *list;
	while (head)
	{
		if ((*list)->fd == fd)
		{
			temp = (*list);
			(*list) = (*list)->next;
			free(temp->data);
			free(temp);
			head = *list;
		}
		else if (head->next && (head->next)->fd == fd)
		{
			temp = head->next;
			head->next = temp->next;
			free(temp->data);
			free(temp);
		}
		else
			head = head->next;
	}
}

int	check_enter(t_list *list, int fd)
{
	int		i;
	t_list	*cur;

	if (!list)
		return (0);
	cur = get_last_node(list, fd, 1);
	if (!cur)
		return (0);
	i = -1;
	while (cur->data[++i])
	{
		if (cur->data[i] == '\n')
			return (1);
	}
	return (0);
}

t_list	*get_last_node(t_list *list, int fd, int flag)
{
	t_list	*temp;
	t_list	*last_node;

	last_node = NULL;
	temp = list;
	if (!list)
		return (NULL);
	while (temp && temp->next)
	{
		if (temp->fd == fd && flag)
			last_node = temp;
		temp = temp->next;
	}
	if (temp && !flag)
		return (temp);
	if (temp->fd == fd)
		last_node = temp;
	return (last_node);
}

void	read_checklist(int fd, t_list **list)
{
	char	*buff;
	ssize_t	read_size;

	read_size = 1;
	while (!check_enter(*list, fd) && read_size != 0)
	{
		buff = (char *)malloc(BUFFER_SIZE + 1);
		if (!buff)
			return ;
		read_size = read(fd, buff, BUFFER_SIZE);
		if ((!*list && !read_size) || read_size == -1)
		{
			free(buff);
			return ;
		}
		buff[read_size] = '\0';
		add_list(list, buff, read_size, fd);
		free(buff);
	}
}
