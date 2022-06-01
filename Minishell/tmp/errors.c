#include "minishell.h"

void	pipe_error(void)
{
	write(2, "minishell: syntax error near unexpected token '|' \n", 51);
	exit_status = 2;
}