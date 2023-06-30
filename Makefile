# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/06 15:09:00 by jinhyeok          #+#    #+#              #
#    Updated: 2023/06/29 21:49:37 by jinhyeok         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
SOURCES = ./src/main.c
NAME = pipex
INCLUDE = ./include
M_OBJ = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(M_OBJ)
	make -C libft
	$(CC) $(CFLAGS) $^ -Llibft -lft -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -I$(INCLUDE) -o $@

clean :
	make -C libft clean
	rm -rf $(M_OBJ)

fclean : clean
	rm -rf $(NAME)

.PHONY: all