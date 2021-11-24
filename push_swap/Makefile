# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/23 16:17:25 by lzylberm          #+#    #+#              #
#    Updated: 2021/11/24 19:41:54 by lzylberm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_CHECKER	= checker.c instruct_checker.c utils.c

SRCS_PS			= push_swap.c instruct.c utils.c sort_small.c small_chunks_1.c small_chunks_2.c big_chunks_1.c big_chunks_2.c big_chunks_3.c sort_all.c

OBJS_CHECKER	= $(SRCS_CHECKER:.c=.o)

OBJS_PS			= $(SRCS_PS:.c=.o)

NAME			= push_swap

CHECKER			= checker

CC			= gcc

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

all:		$(NAME) $(CHECKER)

checker:	$(OBJS_CHECKER)
			CC -o $(CHECKER) $(OBJS_CHECKER)

$(NAME):	$(OBJS_PS)
			CC -o $(NAME) $(OBJS_PS)

clean:
			$(RM) $(OBJS_CHECKER) $(OBJS_PS)

fclean:		clean
			$(RM) $(NAME) $(CHECKER)

re:			fclean all

.PHONY:		all clean fclean re
