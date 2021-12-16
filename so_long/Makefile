# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/26 15:30:08 by lzylberm          #+#    #+#              #
#    Updated: 2021/12/16 18:11:54 by lzylberm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= so_long.c put_map.c moves.c get_next_line.c get_next_line_utils.c

OBJ				= $(SRCS:.c=.o)

NAME			= so_long

VPATH			= src:src/gnl

CC				= gcc

RM 				= rm -f

CFLAGS			= -Wall -Wextra -Werror

MLX 			= libmlx.dylib

LIBS			= -Lmlx -lmlx -framework OpenGL -framework AppKit -lm

all:			$(NAME)

$(NAME):		$(MLX) $(OBJ)
				CC ${CFLAGS} -o ${NAME} ${OBJ} ${LIBS}

%.o: %.c
				$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@


$(MLX):
				@$(MAKE) -C mlx
				@mv mlx/$(MLX) .

clean:
				$(RM) $(OBJ)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)
