#include "minishell.h"

static void	get_args(t_cmd_line *cmd)
{
	t_token	*cur_t;
	int		i;

	cur_t = cmd->tokens;
	i = 0;
	while (cur_t)
	{
		if (cur_t->type == ARG || cur_t->type == BUILTIN)
		{
			cmd->argv[i] = cur_t->str;
			i++;
		}
		cur_t = cur_t->next;
	}
	cmd->argv[i] = NULL;
}

static int	get_nbr_arg(t_cmd_line *cmd)
{
	t_token	*cur_t;
	int		len;

	len = 0;
	cur_t = cmd->tokens;
	while (cur_t)
	{
		if (cur_t->type == ARG || cur_t->type == BUILTIN)
			len++;
		cur_t = cur_t->next;
	}
	return (len);
}

/* For each command, create an array of strings containing the arguments to the command
   (the executable to launch or the built-in to call).
*/
int	get_argv(t_cmd_line **cmd_line)
{
	t_cmd_line	*cur_c;
	int			arg_nb;
	char		**new;

	cur_c = *cmd_line;
	while (cur_c)
	{
		arg_nb = get_nbr_arg(cur_c);
		new = malloc(sizeof(char *) * (arg_nb + 1));
		if (new == NULL)
			return (50);
		cur_c->argv = new;
		get_args(cur_c);
		cur_c = cur_c->next;
	}
	return (0);
}