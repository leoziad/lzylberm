# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/22 17:13:17 by lzylberm          #+#    #+#              #
#    Updated: 2021/11/22 20:12:57 by lzylberm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



SRCS_CLIENT		= client.c

SRCS_SERVER		= server.c utils.c

OBJS_SERVER		= $(SRCS_SERVER:.c=.o)

OBJS_CLIENT		= $(SRCS_CLIENT:.c=.o)

NAME			= server

CLIENT			= client

CC			= gcc

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

all:		$(NAME) $(CLIENT)

client:		$(OBJS_CLIENT)
			CC -o $(CLIENT) $(OBJS_CLIENT)

$(NAME):	$(OBJS_SERVER)
			CC -o $(NAME) $(OBJS_SERVER)

clean:
			$(RM) $(OBJS_SERVER) $(OBJS_CLIENT)

fclean:		clean
			$(RM) $(NAME) $(CLIENT)

re:			fclean all

.PHONY:		all clean fclean re
