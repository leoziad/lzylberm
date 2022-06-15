
SRCS		= ft_putchar.c ft_swap.c ft_putstr.c ft_strlen.c ft_strcmp.c ft_atoi.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncpy.c ft_strncmp.c ft_strcmp.c ft_strlcat.c ft_strdup.c ft_strjoin.c ft_strlcpy.c ft_strnew.c ft_strcpy.c ft_memset.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_bzero.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c ft_substr.c ft_strtrim.c ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c ft_strmapi.c ft_itoa.c ft_split.c

BONUSSRCS	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c 

OBJS		= $(SRCS:.c=.o)

BONUSOBJS	= $(BONUSSRCS:.c=.o)

NAME		= libft.a

CC			= gcc

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror -Iincludes

$(NAME):	$(OBJS)
			ar rcs $(NAME) $(OBJS)

all:		$(NAME)

clean:
			$(RM) $(OBJS) $(BONUSOBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

bonus:		$(BONUSOBJS)
			ar rcs $(NAME) $(BONUSOBJS)

.PHONY:		all clean fclean re bonus
