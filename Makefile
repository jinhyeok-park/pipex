# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/06 15:09:00 by jinhyeok          #+#    #+#              #
#    Updated: 2023/07/10 12:03:44 by jinhyeok         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
SOURCES = ./src/main.c ./src/error.c ./src/cmd.c ./src/free.c ./src/process.c
SOURCES_BONUS = ./src_bonus/main_bonus.c ./src/error.c ./src/cmd.c ./src/free.c\
 ./src_bonus/get_next_line.c ./src_bonus/get_next_line_utils.c \
  ./src_bonus/pipe_control_bonus.c ./src_bonus/process_bonus.c

NAME = pipex
INCLUDE = ./include
M_OBJ = $(SOURCES:.c=.o)
B_OBJ = $(SOURCES_BONUS:.c=.o)

all: MANDATORY_FILE

MANDATORY_FILE: $(M_OBJ)
	rm -rf BONUS_FILE
	make -C libft
	$(CC) $(CFLAGS) -Llibft -lft $^ -o $(NAME)
	touch $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -I$(INCLUDE) -o $@

bonus : BONUS_FILE

BONUS_FILE: $(B_OBJ)
	rm -rf MANDATORY_FILE
	make -C libft
	$(CC) $(CFLAGS) -Llibft -lft $^ -o $(NAME)
	touch $@

clean :
	make -C libft clean
	rm -rf $(M_OBJ) $(B_OBJ);

fclean : clean
	make -C libft fclean
	rm -rf MANDATORY_FILE
	rm -rf BONUS_FILE
	rm -rf $(NAME)
re :
	make fclean
	make all

.PHONY: all