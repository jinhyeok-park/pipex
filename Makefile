# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/06 15:09:00 by jinhyeok          #+#    #+#              #
#    Updated: 2023/06/29 20:46:55 by jinhyeok         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
SOURCES = main.c
B_SOURCES = 

M_OBJ = $(SOURCES:.c=.o)
B_OBJ = $(B_SOURCES:.c=.o)

ifdef BONUS
	OBJECTS = $(B_OBJ)
	NAME = pipex_bonus
else
	OBJECTS = $(M_OBJ)
	NAME = pipex
endif

all	: $(NAME)

$(NAME) : $(OBJECTS)
	make -C libft
	cp ./libft/libft.a ./libft.a

%.o : %.c
	$(CC) $(CFLAGS) -Llibft -lft -c $< -o $@
bonus :
	make BONUS=1 all
clean :
	make -c ft_printf clean
	rm -rf $(M_OBJ) $(B_OBJ)

fclean : clean
	rm -rf pipex
	rm -rf pipex_bonus

re :
	make fclean
	make all

.PHONY : all clean fclean re bonus