/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:24:01 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/07/04 15:05:45 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	int				fd;
	char			*data;
	struct s_list	*next;
}	t_list;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif

size_t	ft_strlen2(char *str);
char	*get_next_line(int fd);
void	free_list(t_list **list, int fd);
int		line_alloc(char **line, t_list *list, int fd);
int		make_line(t_list *list, char **line, int fd);
void	read_checklist(int fd, t_list **list);
void	add_list(t_list **list, char *buff, ssize_t read_size, int fd);
int		check_enter(t_list *list, int fd);
t_list	*get_last_node(t_list *list, int fd, int flag);
void	clear_set(int enter_index, t_list **list, int fd, t_list *backup);

#endif