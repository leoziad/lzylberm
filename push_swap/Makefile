# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/23 16:17:25 by lzylberm          #+#    #+#              #
#    Updated: 2021/12/14 19:05:47 by lzylberm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_CHECKER	= checker.c instruct_checker.c instruct_checker_2.c instruct_checker_3.c list_instruct.c ft_lists.c get_next_line.c get_next_line_utils.c utils.c

SRCS_PS			= push_swap.c instruct.c instruct_2.c instruct_3.c ft_lists.c utils.c index.c sort_small.c small_chunks_1.c small_chunks_2.c big_chunks_1.c big_chunks_2.c big_chunks_3.c sort_all.c

OBJS_CHECKER	= $(SRCS_CHECKER:.c=.o)

OBJS_PS			= $(SRCS_PS:.c=.o)

VPATH			= src:src/gnl:src/checker:src/chunks

PS			= push_swap

CHECKER			= checker

CC				= gcc

RM				= rm -f

CFLAGS			= -Wall -Wextra -Werror

all:			$(PS)

checker:		$(OBJS_CHECKER)
				@CC -o $(CHECKER) $(OBJS_CHECKER)

bonus:			$(PS) $(OBJS_CHECKER)
				@CC -o $(CHECKER) $(OBJS_CHECKER) && CC -o $(PS) $(OBJS_PS)
	
$(PS):			$(OBJS_PS)
				@CC -o $(PS) $(OBJS_PS)

clean:
				@$(RM) $(OBJS_CHECKER) $(OBJS_PS)

fclean:			clean
				@$(RM) $(PS) $(CHECKER)

re:				fclean all

.PHONY:			all clean fclean re
