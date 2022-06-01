SOURCES =	main.c \
			philosophers_utils.c \
			philosophers_utils2.c \
			init.c \
			forks.c \
			print.c \
			error.c

OBJS = $(SOURCES:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I. -fsanitize=thread

NAME = philo

HEADER = philosophers.h

# make -C -Idir Include ?

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
		${CC} ${CFLAGS} -o $(NAME) $(OBJS) -pthread -g

clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME) 

re: fclean all

.PHONY: all clean fclean re
