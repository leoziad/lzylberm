#include "minishell.h"

/* Transforms the environment array of strings into a chained list, making
   future manipulations easier.
*/
int    get_env(char **envp)
{
	t_env	**env_list;
	int		i;

	env_list = get_env_adress();
	i = 0;
	while (envp[i])
		i++;
	i--;
	while (i >= 0)
	{
		if (push_front(envp[i], env_list, 0) == 50)
		{
			clean_env_list(env_list);
			return (50);
		}
		i--;
	}
	return (0);
}

/* Declares a static pointer to the first node of the environment list.
   Whenever this function is subsequently called, it returns the adress to
   this pointer but doesn't set its value to NULL (since it's a static).
*/
t_env    **get_env_adress(void)
{
	static t_env	*env = NULL;

    return(&env);
}

/* Modifies the environment.
   If "modif" == FREE : frees the environment list.
   If "modif" == DELETE : deletes a variable from the environment. 
   If "modif" == ADD : adds a variable to the environment. 
*/
int	env_modif(char *str, int modif)
{
	t_env	**env_list;

	env_list = get_env_adress();
	if (modif == FREE)
		clean_env_list(env_list);
	if (modif == DELETE)
	{
		ft_delete_env_call(env_list, str);
		return (0);
	} 
	if (modif == ADD)
	{
		if (ft_add_value_to_env(env_list, str, 0) == 50)
		{
			clean_env_list(env_list);
			return (50);
		}
	} 
	return (0);
} 

/* Transofrms the environment chained list back to an array of strings,
   to be passed to the execve function for execution.
*/
char	**get_env_tab(t_env **envp)
{
	char	**new;
	t_env	*cur;
	int		i;

	i = 0;
	cur = *envp;
	while (cur)
	{
		cur = cur->next;
		i++;
	}
	new = malloc(sizeof(char *) * (i + 1));
	new[i] = NULL;
	cur = *envp;
	i = 0;
	while (cur)
	{
		new[i] = cur->str;
		i++;
		cur = cur->next;
	}
	return (new);
}

/* Returns the length of the name of an environment variable (the part
   of the string that is before the '=' sign).
*/
int	ft_get_lenkey(char *env_var)
{
	int	i;

	i = 0;
	while (env_var[i] != '\0' && env_var[i] != '=')
		i++;
	return (i);
}

/* Searches for a match between a string and the names of environment
   variables. If it finds a match, returns a pointer to the value of 
   that variable (the part of the string following the '=' sign).
*/
char	*ft_get_value_of_env(t_env **env, char *str)
{
	t_env	*cpy;
	int		len;

	len = ft_get_lenkey(str);
	cpy = *env;
	while (cpy)
	{
		if (len == ft_get_lenkey(cpy->str) && !ft_strncmp(cpy->str, str, len))
			return (cpy->str + len + 1);
		cpy = cpy->next;
	}
	return (NULL);
}

/* Fetches the value of an environment variable.
*/
char	*get_env_var(char *str)
{
	t_env	**env_list;

	env_list = get_env_adress();
	return (ft_get_value_of_env(env_list, str));
}

/* Returns the length of an environment variable invocation (the part of
   a token string that starts with a '$' sign and continues with alpha-
   numerical characters or '_').
*/
int	get_len_env_var(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '$')
		str++;
	if (str[0] && str[0] == '?')
		return (1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

/* Allocates a string containing only a '$' sign, and increments the index
   of our position on the source string.
*/
char	*alloc_dollar(int *cur)
{
	char	*new;

	*cur = *cur + 1;
	new = malloc(sizeof(char) * 2);
	if (new)
	{
		new[0] = '$';
		new[1] = '\0';
		return (new);
	}
	return (NULL);
}

/* If necessary during word expansion, replaces an invocation of an
   environment variable (with the '$' sign) by the value of that
   environment variable.
*/
char	*replace_env_var(char *str, int *cur)
{
	int		len_str;
	char	*cpy;
	char	*env;

	cpy = NULL;
	len_str = get_len_env_var(str);
	if (len_str == 0)
		return (alloc_dollar(cur));
	if (len_str == 1 && str[1] == '?')
	{
		*cur = *cur + 2;
		return (ft_itoa(exit_status));
	}
	cpy = malloc(sizeof(char) * (len_str + 1));
	if (cpy == NULL)
		return (NULL);
	cpy = ft_strncpy(cpy, str + 1, len_str);
	env = get_env_var(cpy);
	free(cpy);
	if (env == NULL)
		return (fake_env(cur, len_str));
	*cur = *cur + len_str + 1;
	cpy = ft_strdup(env);
	return (cpy);
}

/* Moves the index of our iteration on the source string to skip the
   invocation of a non existing environment variable, and returns an
   empty string.
*/
char	*fake_env(int *j, int len_str)
{
	char	*new;

	new = NULL;
	*j = *j + len_str + 1;
	new = malloc(sizeof(char));
	if (new == NULL)
		return (NULL);
	new[0] = '\0';
	return (new);
}

/* Replaces an invocation of an environment variable by the corresponding
   value. If no existing variable corresponds to the one we're looking for,
   discards the token where the invocation took place.
*/
char	*string_env(char *str, char *tmp, int *cur)
{
	char	*tmp2;

	tmp2 = NULL;
	tmp2 = replace_env_var(str, cur);
	if (tmp2 == NULL)
		return (free_str_ret_null(tmp));
	return (tmp2);
}