#include "minishell.h"

int	print_exit_free_env_all(t_cmd_line **cmd)
{
	write(1, "exit\n", 5);
	free_env();
	return (free_all(cmd));
}

void	free_end(t_cmd_line **cmd, char *str)
{
	if (str)
		free(str);
	free_all(cmd);
}

void	free_env(void)
{
	env_modif(NULL, FREE);
}

void	clean_env_list(t_env **env)
{
	t_env	*cpy;
	t_env	*tmp;

	cpy = *env;
	tmp = cpy;
	while (cpy)
	{
		tmp = cpy;
		cpy = cpy->next;
		free(tmp->str);
		free(tmp);
	}
}

void	free_tokens(t_cmd_line **cmd_line)
{
	t_token	*tok;

	while ((*cmd_line)->tokens)
	{
		tok = (*cmd_line)->tokens->next;
		if ((*cmd_line)->tokens->str)
			free((*cmd_line)->tokens->str);
		free((*cmd_line)->tokens);
		(*cmd_line)->tokens = tok;
	}
}

char	*free_str_ret_null(char *s1)
{
	if (s1)
		free(s1);
	return (NULL);
}

void	free_both(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return ;
}

int	free_token_malloc_error(t_token *tok)
{
	if (tok)
		free(tok);
	return (50);
}

int	free_all(t_cmd_line **cmd_line)
{
	t_cmd_line	*tmp;

	if (cmd_line)
	{
		while (*cmd_line)
		{
			tmp = (*cmd_line)->next;
			if ((*cmd_line)->string)
				free((*cmd_line)->string);
			if ((*cmd_line)->argv)
				free((*cmd_line)->argv);
			if ((*cmd_line)->tokens)
				free_tokens(cmd_line);
			if ((*cmd_line)->name_file)
				free((*cmd_line)->name_file);
			free((*cmd_line));
			*cmd_line = tmp;
		}
	} 
	return (1);
}

int	free_malloc_error(t_cmd_line **cmd_line, char *line)
{
	free(line);
	free_all(cmd_line);
	return (50);
}

int	free_all_error(t_cmd_line **cmd, char *str, int error)
{
	if (error == 40)
		write(2, "pipe fails\n", 11);
	if (error == 50)
		write(2, "malloc error\n", 13);
	free(str);
	ft_clean_env();
	free_all(cmd);
	return (1);
}

int	free_str_ret_malloc_error(char *str)
{
	free(str);
	return (50);
}

int	free_str_all_ret_malloc_error(t_cmd_line **cmd, char *str)
{
	free(str);
	free_all(cmd);
	return (50);
}

int	free_all_env_str_ret_malloc_error(t_cmd_line **cmd, char *str)
{
	free(str);
	free_all(cmd);
	ft_clean_env();
	write(2, "malloc error\n", 13);
	return (50);
}

void	free_fd_all_exit_malloc_error(t_cmd_line **cmd_line)
{
	close_fd_all(cmd_line);
	exit (50);
}

void	free_str_fd_all_env_pid_exit(t_cmd_line **cmd_line,
	pid_t *pid, char **str)
{
	free_all(cmd_line);
	ft_clean_env();
	free(pid);
	free(str);
	exit(1);
}

char	*write_bad_cmd_free(char *str)
{
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, " : commande introuvable\n",
		ft_strlen(" : commande introuvable\n"));
	free(str);
	return (NULL);
}

char	*write_bad_cmd_free_split(char *str, char **split_path)
{
	free_split(split_path);
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, " : commande introuvable\n",
		ft_strlen(" : commande introuvable\n"));
	return (NULL);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i])
		{
			free(split[i]);
			i++;
		}
	}
	if (split)
		free(split);
}

char	*free_split_ret_null(char **split_path)
{
	free_split(split_path);
	return (NULL);
}

char	*free_split_ret_str(char **split, char *str)
{
	free_split(split);
	return (str);
}

char	*free_split_token(char **split, t_token *tok)
{
	free_split(split);
	if (tok)
	{
		if (tok->str)
			free(tok->str);
	}
	return (NULL);
}

void	free_str_fd_exit_malloc_error(char **str, t_cmd_line **cmd_line)
{
	free(str);
	close_fd_all(cmd_line);
	exit (50);
}

/* unlink */

void	free_file_name(char *file_name)
{
	if (file_name != NULL)
	{
		unlink(file_name);
		free(file_name);
	}
}

void	ft_clean_env(void)
{
	env_modif(NULL, FREE);
}

int	free_cmdl_ret_malloc_error(t_cmd_line *stc)
{
	if (stc)
		free(stc);
	return (50);
}