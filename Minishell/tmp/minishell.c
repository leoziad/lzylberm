#include "minishell.h"


/* 
*/
void	signal_handler(int sig)
{
	exit_status += sig;
	if (sig == 2)
	{
		exit_status = 130;
		printf("\n");
		rl_on_new_line();
//		rl_replace_line("", 0);
		rl_redisplay();
	}
//	if (sig == SIGQUIT)
//	{
//		write(2, "Quit (core dumped)\n", 19);
//		exit (1);
//	}
}

/* Checks that the pipeline of the command line is valid : no pipe at the
   start and no consecutive pipes.
*/
int	check_pipeline(char *line)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '|')
			word = 1;
		if (line[i] == '|')
		{
			if (word == 0)
				return (1);
			word = 0;
		}
		i++;
	}
	if (word == 0)
		return (1);
	return (0);
}

/* Check that any existing quotes are closed.
   Cut the command line string into single commands.
   Break each single command into tokens.
   Expand words : get rid of quotation marks and replace any invocation
   of an environment variable by its value.
   Parse the tokens to determine the arguments of every command.
*/
int	parser(t_cmd_line **cmd_line, char *line)
{
	int	ret;

	ret = check_quote_closure(line);
	if (ret > 0)
	{
		write(2, "minishell: open quotes\n", 23);
		free_all(cmd_line);
	}
	else
	{
		if (get_cmd_line(cmd_line, line) > 0)
			return (free_malloc_error(cmd_line, line));
		if (tokenize_cmd_line(cmd_line) > 0)
			return (free_malloc_error(cmd_line, line));
		ret = word_expansion(cmd_line);
		if (ret != 0)
		{
			free_all(cmd_line);
			if (ret == 50)
				return (free_str_ret_malloc_error(line));
		}
		if (get_argv(cmd_line) != 0)
			return (free_str_all_ret_malloc_error(cmd_line, line));
	}
	return (ret);
}

/* Parse the command line, and if everything is ok pass the result of
   the parsing to the executer. 
*/
void	parse_and_execute(t_cmd_line **cmd_line, char *line)
{
	int	ret;

	ret = parser(cmd_line, line);
	if (ret == 50)
	{
		free_all_env_str_ret_malloc_error(cmd_line, line);
		exit (1);
	}
	if (ret == 0)
	{
		if (line != NULL && *cmd_line != NULL)
		{
			ret = execute(cmd_line);
			if (ret != 0)
			{
				free_all_error(cmd_line, line, ret);
				exit (1);
			}
		}
	}
}

/* Returns CLOSED (0) if no quotes are left opened.
   Returns SINGLE (1) if single quotes are left opened.
   Returns DOUBLE (2) if double quotes are left opened.
*/
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

/* While iterating on a string : 
   - if you find a single quote outside of quotes, you're now inside
   single quotes.
   - if you find single quotes inside single quotes, that quote is 
   now closed.
   - if you find single quotes inside double quotes, those are not
   to be treated as quotation marks ('quote' doesn't change)
   Same for double quotes, mutatis mutandis.
*/
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

/* Ad hoc function to manage quotation marks while expanding words in 
   tokens.
   Sets the token's boolean variable "expanded" to true.
*/
t_quote	update_quote_succes(t_token *cur_t, int *i, t_quote quote, char **s1)
{
	(*i)++;
	cur_t->expanded = true;
	if (*s1 == NULL)
	{
		*s1 = malloc(sizeof(char));
		if (*s1 != NULL)
			(*s1)[0] = '\0';
	}
	return (quote);
}

/* Iterate on a string until the end, or until you find a pipe '|' that
   is not between quotes.
*/
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

/* Allocates a new node in the command line chained list. Initializes it
   and stores the string associated with the command in it.
*/
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

/* Isolate each single command in the command line by creating a 
   chained list, where each node contains a portion of the command
   line string seperated from others by a pipe '|'.
*/
int	get_cmd_line(t_cmd_line **cmd_line, char *line)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (line[i])
	{
		if (i != 0)
		{
			i++;
			start++;
		}
		go_to_end_of_cmd(&i, line);
		if (get_cmd(line, i, start, cmd_line) > 0)
			return (50);
		start = i;
		if (i == 0)
		{
			i++;
			start++;
		}
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

int main(int ac, char **av, char **envp)
{
    char        *line;
    t_cmd_line  *cmd_line;

	exit_status = 0;
    cmd_line = NULL;
    get_env(envp);
    signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);

    int i = 0;
    while (1)
    {
        signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		line = readline("minishell$> ");
		add_history(line);
        if (line == NULL)
            return (print_exit_free_env_all(&cmd_line));
		if (check_pipeline(line))
			pipe_error();
		else
			parse_and_execute(&cmd_line, line);
		free_end(&cmd_line, line);
    }
    return (0);
}