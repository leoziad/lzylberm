#include "minishell.h"

/* Copies the string of the token (tok_str) into a new string (str).
   Frees tok_str because it's gonna be replaced by the expanded token (final_str).
*/ 
char	*init_str(char **str, char *tok_str, int *i, char **final_str)
{
	*final_str = NULL;
	*i = 0;
	*str = ft_strdup(tok_str);
	free(tok_str);
	if (*str == NULL)
		return (NULL);
	return (*str);
}

char	*new_token_env(t_token **stc, char **split, int i)
{
	t_token	*next;
	t_token	*new;

	if ((*stc))
		next = (*stc)->next;
	while (split[i])
	{
		new = malloc(sizeof(t_token));
		if (new == NULL)
			return (free_split_ret_str(split, NULL));
		init_token(new);
		new->type = ARG;
		new->str = ft_strdup(split[i]);
		if (new->str == NULL)
			if (new)
				return (free_split_token(split, new));
		if ((*stc))
			new->next = next;
		(*stc)->next = new;
		(*stc) = (*stc)->next;
		i++;
	}
	free_split(split);
	return (new->str);
}

/* If the word contains no environment variable invocation, we just need to
   go to the end of the word (end of string, new quotation mark or a '$'
   signifying an environment variable invocation).
*/
char	*regular_expansion(char *str, int *i, char *final_str)
{
	char	*new;
	char	*join;
	int		start;

	start = *i;
	while (str[(*i)] && str[(*i)] != '\'' && str[(*i)] != '"'
		&& str[(*i)] != '$')
		(*i)++;
	new = malloc(sizeof(char) * ((*i) - start + 1));
	if (new == NULL)
		return (free_str_ret_null(final_str));
	new = ft_strncpy(new, str + start, ((*i) - start));
	join = ft_strjoin(final_str, new);
	free_both(final_str, new);
	return (join);
}

/* Expand a word consisting of an environment variable invocation.
   Replace the environment variable invocation ("$HOME" for example) by the
   variable's value.
   Split the string obtained around spaces in case there are some 
*/
char	*variable_expansion(t_token **cur_t, char *str, char *final_str, int *i)
{
	char	*env;
	char	**split;
	char	*join;

	env = string_env(str, final_str, i);
	if (env == NULL)
		return (free_str_ret_null(final_str));
	split = ft_split(env, ' ');
	int j = 0;
	while (split[j])
	{
		printf("split[%d] = %s\n", j, split[j]);
		j++;
	}
	free(env);
	if (split == NULL)
		return (free_str_ret_null(final_str));
	join = ft_strjoin(final_str, split[0]);
	if (final_str == NULL && split[0] == NULL)
	{
		join = malloc(sizeof(char));
		join[0] = '\0';
	}
	free(final_str);
	if (split[0] == NULL || split[1] == NULL)
		return (free_split_ret_str(split, join));
	(*cur_t)->str = join;
	return (new_token_env(cur_t, split, 1));
}

/* Expand a word that is inside single quotes.
   Environment variables need not be expanded.
*/
char	*single_expansion(char *str, int *i, char *final_str)
{
	char	*s2;
	char	*s3;
	int		j;

	s2 = NULL;
	s3 = NULL;
	j = *i;
	while (str && str[(*i)] && str[(*i)] != '\'')
		(*i)++;
	s2 = malloc(sizeof(char) * ((*i) - j + 1));
	if (s2 == NULL)
	{
		if (final_str)
			free(final_str);
		return (NULL);
	}
	s2 = ft_strncpy(s2, str + j, (*i) - j);
	s3 = ft_strjoin(final_str, s2);
	free_both(final_str, s2);
	return (s3);
}

/* Expand a word that is inside double quotes.
   If the first character is a '$', an environment variable needs to be expanded.
*/
char	*double_expansion(t_token **cur_t, char *str, int *i, char *final_str)
{
	while (str && str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
		{
			final_str = variable_expansion(cur_t, str, final_str, i);
			if (final_str == NULL)
				return (NULL);
		}
		else
		{
			final_str = regular_expansion(str, i, final_str);
			if (final_str == NULL)
				return (NULL);
		}
	}
	return (final_str);
}

/* Expand a word that is not inside quotation marks.
   If the first character is a '$', an environment variable needs to be expanded.
*/
char	*closed_expansion(t_token **cur_t, char *str, int *i, char *final_str)
{
	while (str[*i] && str[*i] != '\'' && str[*i] != '"')
	{
		if (str[*i] && str[*i] == '$') 
		{
			final_str = variable_expansion(cur_t, str, final_str, i);
			if (final_str == NULL)
			{
				return (NULL);
			}
		}
		else if (str[*i] != '$')
		{
			final_str = regular_expansion(str, i, final_str);
			if (final_str == NULL)
				return (NULL);
		}
		
	}
	return (final_str);
}

/* Frees strings that we don't need any more, and assigns the expanded string 
   to the appropriate node of our tokens chained list.
*/
int	expansion_return(char *str, t_token **stc, char *s1)
{
	free(str);
	(*stc)->str = s1;
	return (0);
}

/* Initializes the different strings we'll use.
   At the start of a word, checks for quotes and launches the appropriate expand function.
   If quotes were found, the token's boolean variable "expanded" will be set to true.
*/
int	expand_word(t_token **stc, char *tok_str, t_quote quote, t_quote prec)
{
	char	*final_str;
	int		i;
	char	*str;

	if (init_str(&str, tok_str, &i, &final_str) == NULL)
		return (50);
	while (str[i])
	{
		quote = update_quote_status(str[i], quote);
		if (prec != quote)
			prec = update_quote_succes(*stc, &i, quote, &final_str);
		else
		{
			if (quote == SINGLE)
				final_str = single_expansion(str, &i, final_str);
			else if (quote == DOUBLE)
				final_str = double_expansion(stc, str, &i, final_str);
			else if (quote == CLOSED)
				final_str = closed_expansion(stc, str, &i, final_str);
		}
		if (final_str == NULL)
			return (free_str_ret_malloc_error(str));
	}
	return (expansion_return(str, stc, final_str));
}

/* Expand words for each token if necessary. 
*/
int	word_expansion(t_cmd_line **cmd_line)
{
	t_cmd_line	*cur_c;
	t_token		*cur_t;
    t_quote     quote;
    t_quote     prec;
	int			ret;

	quote = CLOSED;
    prec = CLOSED;
    cur_c = *cmd_line;
	ret = 0;
	while (cur_c)
	{
		cur_t = cur_c->tokens;
		while (cur_t)
		{
			if (cur_t->str && cur_t->str[0] != '\0')
			{
				ret = expand_word(&cur_t, cur_t->str, quote, prec);
				if (ret != 0)
					return (50);
			}
			cur_t = cur_t->next;
		}
		cur_c = cur_c->next;
	}
	return (0);
}