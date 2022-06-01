#include "minishell.c"

int	print_exit_free_env_all(t_cmd_line **cmd)
{
	write(1, "exit\n", 5);
	free_env();
	return (free_all(cmd));
}

