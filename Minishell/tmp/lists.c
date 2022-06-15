#include "minishell.h"

int	push_front(char *env, t_env **begin_lst, int declare)
{
	t_env	*env_new;

	env_new = malloc(sizeof(t_env));
	if (env_new == NULL)
		return (50);
	env_new->str = ft_strdup(env);
	if (env_new->str == NULL)
		return (50);
	env_new->declare = declare;
	env_new->next = *begin_lst;
	*begin_lst = env_new;
	return (0);
}

void	cmdl_add_back(t_cmd_line **first, t_cmd_line *add_back)
{
	t_cmd_line	*cur;

	cur = *first;
	if (cur == NULL)
		*first = add_back;
	else
	{
		while (cur->next)
			cur = cur->next;
		cur->next = add_back;
	}
}