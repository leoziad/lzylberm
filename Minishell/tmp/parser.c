#include "minishell.c"

int check_quote_closure(char *line)
{
	int		i;
	t_quote	quote;

	i = 0;
	quote = CLOSED;
	while (line[i])
	{
		if (line[i] == '"')
		{
			if (quote == CLOSED)
				quote = DOUBLE;
			else if (quote == DOUBLE)
				quote = CLOSED;
		}
		else if (line[i] == '\'')
		{
			if (quote == CLOSED)
				quote = SINGLE;
			else if (quote == SINGLE)
				quote = CLOSED;
		}
		i++;
	}
	return (quote);
}

t_quote	update_quote_status(char c, t_quote quote)
{
	if (c == '"')
	{
		if (quote == CLOSED)
			return (DOUBLE);
		else if (quote == DOUBLE)
			return (CLOSED);
	}
	if (c == '\'')
	{
		if (quote == CLOSED)
			return (SINGLE);
		else if (quote == SINGLE)
			return (CLOSED);
	}
	return (quote);
}

t_quote	update_quote_succes(t_token *stc, int *i, t_quote quote, char **s1)
{
	(*i)++;
	stc->expanded = true;
	if (*s1 == NULL)
	{
		*s1 = malloc(sizeof(char));
		if (*s1 != NULL)
			(*s1)[0] = '\0';
	}
	return (quote);
}

static void	go_to_end_of_cmd(int *i, char *str)
{
	t_quote	quote;

	quote = CLOSED;
	while (str[*i])
	{
		quote = update_quote_status(str[*i], quote);
		if (str[*i] == '|' && quote == CLOSED)
			return ;
		(*i)++;
	}
	return ;
}

static void	init_cmd(t_cmd_line *new)
{
	new->string = NULL;
	new->tokens = NULL;
	new->argv = NULL;
	new->name_file = NULL;
	new->next = NULL;
}

static int	get_cmd(char *str, int i, int start, t_cmd_line **first)
{
	t_cmd_line	*new;

	new = malloc(sizeof(t_cmd_line));
	if (new == NULL)
		return (50);
	init_cmd(new);
	new->string = malloc(sizeof(char) * (i - start + 1));
	if (new->string == NULL)
		return (free_cmdl_ret_malloc_error(new));
	new->string = ft_strncpy(new->string, str + start, i - start);
	cmdl_add_back(first, new);
	return (0);
}

int	get_cmd_line(t_cmd_line **cmd_line, char *line)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (line[i])
	{
		go_to_end_of_cmd(&i, line);
		if (get_cmd(line, i, start, cmd_line) > 0)
			return (50);
		i++;
		start = i;
	}
	return (0);
}

int	is_redirection(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_separator(char c)
{
	if (c == ' ' || c == '<' || c == '>')
		return (1);
	return (0);
}

void	iter_to_end_of_redirection(char	*str, int *i)
{
	char	c;

	c = str[*i];
	while (str[*i] && str[*i] == c)
		(*i)++;
}

int	iter_to_end_of_token(int *cur, char *str)
{
	t_quote	quote;

	quote = CLOSED;
	while (str[(*cur)])
	{
		quote = update_quote_status(str[*cur], quote);
		if (is_separator(str[*cur]) == 1 && quote == CLOSED)
			break ;
		(*cur)++;
	}
	return (0);
}