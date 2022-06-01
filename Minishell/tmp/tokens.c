#include "minishell.h"

void	init_token(t_token *new)
{
	new->str = NULL;
	new->type = NON;
	new->expanded = false;
	new->next = NULL;
}

/* Compares a token string with the names of built-ins.
   Returns 0 if the comparison is unsuccessful.
   Returns 2 if the string is "exit".
   Returns 1 if it's any other built-in.
*/
int	ft_is_builtin(char *str)
{
	if (str == NULL)
		return (0);
	if (!ft_strcmp("exit", str))
		return (2);
	if (!ft_strcmp("cd", str))
		return (1);
	else if (!ft_strcmp("echo", str))
		return (1);
	else if (!ft_strcmp("env", str))
		return (1);
	else if (!ft_strcmp("pwd", str))
		return (1);
	else if (!ft_strcmp("export", str))
		return (1);
	else if (!ft_strcmp("unset", str))
		return (1);
	return (0);
}

/* Determines and assigns the correct type to the current token.
*/
void	init_type(t_token *new)
{
	int	len;

	len = 0;
	if (new->str)
		len = ft_strlen(new->str);
	if (len == 1)
	{
		if (new->str[0] == '<')
			new->type = INPUT_REDIRECT;
		else if (new->str[0] == '>')
			new->type = OUTPUT_REDIRECT;
	}
	if (len == 2)
	{
		if (new->str[0] == '<' && new->str[1] == '<')
			new->type = HERE_DOC;
		if (new->str[0] == '>' && new->str[1] == '>')
			new->type = APPEND_OUTPUT_REDIRECT;
	}
	if (ft_is_builtin(new->str))
		new->type = BUILTIN;
	if (new->type == NON && len != 0)
		new->type = ARG;
}

/* Utility to add a token at the back of a list.
*/
void	token_add_back(t_token **tokens, t_token *new)
{
	t_token	*tmp;

	tmp = *tokens;
	if (tmp == NULL)
		*tokens = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

/* Allocates a new node for a tokens chained list, initializes its
   value (the string it's composed of), its type, and adds it to the
   list.
*/
static int	add_token(int i, int start, char *str, t_cmd_line **cmd)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (50);
	init_token(new);
	new->str = malloc(sizeof(char *) * (i - start + 1));
	if (new->str == NULL)
		return (free_token_malloc_error(new));
	new->str = ft_strncpy(new->str, str + start, i - start);
	init_type(new);
	token_add_back(&((*cmd)->tokens), new);
	return (0);
}

/* Cuts each command into tokens. Trims trailing spaces. Tokens are
   separated by spaces or redirections. Tokens are stored as a chained
   list and passed to the corresponding command line node.
*/
static int	get_tokens(t_cmd_line **cmd)
{
	int		i;
	int		start;
	int		len;

	i = 0;
	len = 0;
	if ((*cmd)->string != NULL)
		len = ft_strlen((*cmd)->string);
	while (i < len)
	{
		while (i < len && (*cmd)->string[i] == ' ')
			i++;
		start = i;
		if ((*cmd)->string[i] && is_redirection((*cmd)->string[i]))
			iter_to_end_of_redirection((*cmd)->string, &i);
		else
			iter_to_end_of_token(&i, (*cmd)->string);
		if (add_token(i, start, (*cmd)->string, cmd) > 0)
			return (50);
	}
	return (0);
}

int	is_type_redirect(t_e_token type)
{
	if (type == OUTPUT_REDIRECT || type == APPEND_OUTPUT_REDIRECT
		|| type == INPUT_REDIRECT || type == HERE_DOC)
		return (1);
	return (0);
}

int	error_syntax_file(t_e_token type)
{
	write(2, "minishell: erreur de syntaxe", 28);
	if (type == NON)
		write(2, " newline\n", 9);
	if (type == OUTPUT_REDIRECT)
		write(2, " >\n", 3);
	else if (type == APPEND_OUTPUT_REDIRECT)
		write(2, " >>\n", 4);
	else if (type == INPUT_REDIRECT)
		write(2, " <\n", 3);
	else if (type == HERE_DOC)
		write(2, " <<\n", 4);
	return (12);
}

/* Iterates on the command line list. For each command, iterates on its
   tokens list. When a here-doc is found, determines the delimiter.
   Prints an error if a necessary delimiter is absent.
*/
int	check_delimiter(t_cmd_line **cmd_line, int delimiter)
{
	t_cmd_line	*cur_c;
	t_token		*cur_t;

	cur_c = *cmd_line;
	while (cur_c)
	{
		cur_t = cur_c->tokens;
		while (cur_t)
		{
			if (cur_t->type == HERE_DOC)
				delimiter = 1;
			else if (delimiter == 1 && cur_t->str && cur_t->str[0] != '\0')
			{
				if (is_type_redirect(cur_t->type))
					return (error_syntax_file(cur_t->type));
				cur_t->type = DELIMITER;
				delimiter = 0;
			}
			cur_t = cur_t->next;
		}
		if (delimiter == 1)
			return (error_syntax_file(NON));
		cur_c = cur_c->next;
	}
	return (0);
}

/* Ad hoc function to keep track of redirections encountered and their
   type.
*/
t_e_token	redir_type_change(t_e_token type, int *redir)
{
	*redir = 1;
	return (type);
}

/* If we encounter an input redirection ('<'), the next token is the
   file the input needs to be redirected from.
   If we encounter an output redirection ('>'), the next token is the
   file the output needs to be redirected to.
   If we encounter an append output redirection ('>>'), the next token
   is the file the output needs to be redirected to in append mode.
   If we encounter a here-doc ('<<'), the next token is the delimiter.
*/
t_e_token	change_type_file(t_e_token type, int *redir)
{
	*redir = 0;
	if (type == INPUT_REDIRECT)
		return (FILE_IN);
	else if (type == OUTPUT_REDIRECT)
		return (FILE_OUT);
	else if (type == APPEND_OUTPUT_REDIRECT)
		return (FILE_OUT_OVER);
	else if (type == HERE_DOC)
		return (DELIMITER);
	return (NON);
}

/* A redirection is present without an argument to redirect to
   or from.
*/ 
int	error_cmd_syntax(t_cmd_line *cur_c)
{
	write(2, "minishell: erreur de syntaxe",
		ft_strlen("minishell: erreur de syntaxe"));
	if (cur_c)
		write(2, " |\n", 3);
	else
		write(2, " newline\n", 9);
	return (12);
}

/* If a command contains a redirection of input or output, identifies
   the token corresponding to the file that needs to be written to or
   read from, and changes its type accordingly.
*/
int	check_open_file(t_cmd_line **cmd_line)
{
	t_cmd_line	*cur_c;
	t_token		*cur_t;
	int			redir;
	t_e_token	type;

	cur_c = *cmd_line;
	redir = 0;
	while (cur_c)
	{
		cur_t = cur_c->tokens;
		while (cur_t)
		{
			if (is_redirection(cur_t->str[0]) == 1 && redir == 1)
				return (error_syntax_file(cur_t->type));
			else if (is_redirection(cur_t->str[0]) == 1)
				type = redir_type_change(cur_t->type, &redir);
			else if (redir == 1 && cur_t->str && (cur_t->str[0] != '\0'))
				cur_t->type = change_type_file(type, &redir);
			cur_t = cur_t->next;
		}
		if (redir == 1)
			return (error_cmd_syntax(cur_c->next));
		cur_c = cur_c->next;
	}
	return (0);
}

/* Cuts each command into tokens, and assigns a specific type to them
   to facilitate execution.
*/
int	tokenize_cmd_line(t_cmd_line **cmd_line)
{
	t_cmd_line	*i;

	i = *cmd_line;
	while (i)
	{
		if (get_tokens(&i) > 0)
			return (50);
		i = i->next;
	}
	if (check_delimiter(cmd_line, 0) != 0 || check_open_file(cmd_line) != 0)
		return (12);
	return (0);
}