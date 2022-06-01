NAME = minishell

LIBFT = srcs/libft

CFLAGS = -g -Wall -Wextra -Werror

LIB =  -lreadline -I/Users/$(USER)/.brew/opt/readline/include -L/Users/$(USER)/.brew/opt/readline/lib

SRC_BUILT_IN = ft_add_val.c ft_built_in_echo.c ft_built_in_echo_fd.c ft_built_in_env.c ft_built_in_env_fd.c ft_built_in_export.c ft_built_in_export_fd.c ft_built_in_free.c ft_built_in_pwd_fd.c ft_built_in_unset.c ft_built_in_pwd.c ft_built_in.c ft_built_in_cd.c ft_delete_key.c ft_error.c ft_free_env.c ft_get_val.c ft_init_env.c  

SRCS = arguments.c env.c errors.c exec.c expansion.c free.c lists.c minishell.c pipes.c tokens.c 

SRCS_BUILT = $(addprefix built-in/, $(SRC_BUILT_IN))

CC = gcc

OBJ  = ${SRCS:.c=.o}

OBJ_BUILT_IN = ${SRCS_BUILT:.c=.o}

OBJS  = *.o

all :
	@make -C $(LIBFT)
	@make $(NAME)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o} -I include/

$(NAME)	: $(OBJ) $(OBJ_BUILT_IN)
	$(CC) $(FLAGS) -I srcs/libft/includes/ -I include/. $(OBJ) $(OBJ_BUILT_IN) srcs/libft/libft.a -o $(NAME) $(LIB)

clean :
		@make clean -C $(LIBFT)
		@rm -rf $(OBJ) $(OBJ_BUILT_IN)

fclean : clean
		@rm -rf libft.a
		@make fclean -C $(LIBFT)
		@rm -rf $(OBJS)
		@rm -rf $(NAME)

re : fclean all