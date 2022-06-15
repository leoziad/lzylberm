#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "srcs/libft/libft.h"
# include <stdbool.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>

int exit_status;

typedef struct s_exec			t_exec;
typedef struct s_token			t_token;
typedef struct s_cmd_line		t_cmd_line;
typedef struct s_env			t_env;

typedef enum quote
{
	CLOSED,
	SINGLE,
	DOUBLE,
}	t_quote;

typedef enum modif
{
	GET,
	DELETE,
	FREE,
	ADD
}			t_modif;

typedef enum token
{
	NON,
	ARG,
	BUILTIN,
	INPUT_REDIRECT,
	HERE_DOC,
	DELIMITER,
	OUTPUT_REDIRECT,
	APPEND_OUTPUT_REDIRECT,
	FILE_IN,
	FILE_OUT,
	FILE_OUT_OVER,
	ENDS
}				t_e_token;

struct		s_exec
{
	char	**argv;
	int		fd_in;
	int		fd_out;
	t_exec	*next;	
};

struct			s_token
{
	char		*str;
	t_e_token	type;
	bool		expanded;
	t_token		*next;
};

struct				s_cmd_line
{
	char			*string;
	t_token			*tokens;
	char			**envp;
	char			**argv;
	int				fd_in;
	int				fd_out;
	char			*name_file;
	t_cmd_line	    *next;
};

struct		s_env
{
	char	*str;
	int		declare;
	t_env	*next;
};

// main functions

void	signal_handler(int sig);
int		parser(t_cmd_line **cmd_line, char *line);
void	parse_and_execute(t_cmd_line **cmd_line, char *line);


// environment functions

int		get_env(char **envp);
void	increment_shell_lvl(char *str);
void	init_shell_lvl(t_env **env_list);
t_env   **get_env_adress();
int		env_modif(char *str, int modif);
char	**get_env_tab(t_env **envp);
int		ft_get_lenkey(char *env_var);
char	*ft_get_value_of_env(t_env **env, char *str);
char	*get_env_var(char *str);
int		get_len_env_var(char *str);
char	*alloc_dollar(int *cur);
char	*replace_env_var(char *str, int *cur);
char	*fake_env(int *j, int len_str);
char	*string_env(char *str, char *tmp, int *cur);

// free functions

int		print_exit_free_env_all(t_cmd_line **cmd);
void    clean_env_list(t_env **env);
void	free_env(void);
int		free_all(t_cmd_line **cmd_line);
int		free_cmdl_ret_malloc_error(t_cmd_line *stc);
int		free_all_error(t_cmd_line **cmd, char *str, int error);
void	free_tokens(t_cmd_line **cmd_line);
int		free_token_malloc_error(t_token *tok);
int		free_str_ret_malloc_error(char *str);
int		free_str_all_ret_malloc_error(t_cmd_line **cmd, char *str);
int		free_all_env_str_ret_malloc_error(t_cmd_line **cmd, char *str);
void	free_fd_all_exit_malloc_error(t_cmd_line **cmd_line);
void	free_str_fd_exit_malloc_error(char **str, t_cmd_line **cmd_line);
void	free_str_fd_all_env_pid_exit(t_cmd_line **cmd_line, pid_t *pid, char **str);
char	*free_str_ret_null(char *s1);
void	free_both(char *s1, char *s2);
int		free_all_error(t_cmd_line **cmd, char *str, int error);
char	*write_bad_cmd_free(char *str);
char	*write_bad_cmd_free_split(char *str, char **split_path);
void	free_split(char **split);
char	*free_split_ret_str(char **split, char *str);
char	*free_split_token(char **split, t_token *tok);
char	*free_split_ret_null(char **split_path);
void	free_file_name(char *file_name);
void	ft_clean_env(void);
void	free_end(t_cmd_line **cmd, char *str);


// exit functions

// lists functions

int		push_front(char *env, t_env **begin_lst, int declare);
void	token_add_back(t_token **tokens, t_token *new);
void	cmdl_add_back(t_cmd_line **first, t_cmd_line *add_back);

// errors functions

void	pipe_error(void);

// parsing functions

int 	check_quote_closure(char *line);
t_quote	update_quote_status(char c, t_quote quote);
t_quote	update_quote_succes(t_token *stc, int *i, t_quote quote, char **s1);
int		is_redirection(char c);
int		is_separator(char c);
int		get_cmd_line(t_cmd_line **cmd_line, char *line);
int		iter_to_end_of_token(int *cur, char *str);
int		get_argv(t_cmd_line **cmd_line);
int		check_pipeline(char *line);
void	iter_to_end_of_redirection(char	*str, int *i);

// tokens functions

void		init_token(t_token *new);
void		init_type(t_token *new);
int			ft_is_builtin(char *str);
int			is_type_redirect(t_e_token type);
int			error_syntax_file(t_e_token type);
int			check_delimiter(t_cmd_line **cmd_line, int delimiter);
t_e_token	redir_type_change(t_e_token type, int *redir);
t_e_token	change_type_file(t_e_token type, int *redir);
int			error_cmd_syntax(t_cmd_line *cur_c);
int			check_open_file(t_cmd_line **cmd_line);
int			tokenize_cmd_line(t_cmd_line **cmd_line);

// word expansion functions

char	*init_str(char **str, char *tok_str, int *i, char **final_str);
char	*single_expansion(char *str, int *i, char *final_str);
char	*double_expansion(t_token **cur_t, char *str, int *i, char *final_str);
char	*closed_expansion(t_token **cur_t, char *str, int *i, char *final_str);
int		expansion_return(char *str, t_token **stc, char *s1);
int		expand_word(t_token **stc, char *tok_str, t_quote quote, t_quote prec);
int		word_expansion(t_cmd_line **cmd_line);
char	*new_token_env(t_token **stc, char **split, int i);
char	*regular_expansion(char *str, int *i, char *final_str);
char	*variable_expansion(t_token **cur_t, char *str, char *final_str, int *i);


// piping functions

int		get_nbr_cmd(t_cmd_line *cmd);
void	free_fd_tab(int **in_out_tab);
int		connect_pipes(int **in_out_tab, int i, t_cmd_line *cur_c);
int		init_pipes(t_cmd_line **cmd_line);
int		redirect_file_in(t_cmd_line **cmd_line, t_token *cur_t, t_e_token type);
int		redirect_file_out(t_cmd_line **cmd_line, t_token *cur_t, t_e_token type);
int		open_fd(t_cmd_line **cmd_line);
void	close_fd_all(t_cmd_line **cmd_line);

// exec functions

void	signal_handler_2(int sig);
int		ft_exec_bd_fd(char *str, char **args, t_cmd_line **cmd_line, pid_t *pid);
int		no_forking(t_cmd_line **cmd, pid_t *pid);
char	*get_acces(char *str, char *path);
int		try_acces(char *str, char *path);
char	*get_bin_argv_zero(char *str, char *path, int i);
int		exec_builtin(char **str, t_cmd_line **cmdl, pid_t *pid);
int		ft_exec_cmd(t_cmd_line **cmdl, char **str, pid_t *pid);
int		ft_execve_fct(t_cmd_line **cmd, t_cmd_line **cmd_line, pid_t *pid);
int		multi_fork(pid_t *pid, int i, t_cmd_line **cmd_line, t_cmd_line **cur_c);
int		forking(t_cmd_line **cmd_line, pid_t *pid);
int		wait_pid(t_cmd_line **cmdl, pid_t *pid);
int		execute(t_cmd_line **cmd_line);
int		write_in_fd(int fd, t_token **cur_t);
int		create_heredoc_fd(t_cmd_line **cmdl, t_token **cur);
char	*random_name(void);
int		aleatori_char(void);

// cleaning functions

int		print_exit_free_env_all(t_cmd_line **cmd);
void	ft_clean_env(void);
void	ft_free_env_elem(t_env *env);
void	free_tokens(t_cmd_line **cmd_line);
int		free_token_malloc_error(t_token *tok);
char	*free_str_ret_null(char *s1);
void	free_both(char *s1, char *s2);
int		free_malloc_error(t_cmd_line **cmd_line, char *line);
int		free_str_ret_malloc_error(char *str);
int		free_str_all_ret_malloc_error(t_cmd_line **cmd, char *str);
int		free_all_env_str_ret_malloc_error(t_cmd_line **cmd, char *str);
void	free_fd_all_exit_malloc_error(t_cmd_line **cmd_line);
void	free_str_fd_all_env_pid_exit(t_cmd_line **cmd_line, pid_t *pid, char **str);
char	*write_bad_cmd_free(char *str);
char	*write_bad_cmd_free_split(char *str, char **split_path);
void	free_split(char **split);
char	*free_split_ret_null(char **split_path);
void	free_str_fd_exit_malloc_error(char **str, t_cmd_line **cmd_line);
void	free_file_name(char *file_name);

// built-in functions

int		ft_add_env(char *str);
char	*ft_final_add(char *env);
int		ft_special_lenkey(char *str);
int		ft_add_value_to_env(t_env **env_list, char *env, int declare);
int		free_in_builin(t_cmd_line **first, pid_t *pid, int ret);
int		ft_sup_int(char *str);
int		ft_non_int(char *str);
int		ft_exec_builtin(char *str, char **args, t_cmd_line **first, pid_t *pid);


int		ft_built_in_echo_fd(char **str, int fd);
int		ft_check_n(char **str);
int		ft_built_in_echo(char **str);

int		ft_built_in_env_fd(char **str, int fd);
void	ft_built_in_show_env_fd(t_env **env, int fd);
int		ft_built_in_env(char **str);
int		ft_is_equal(char *str);
void	ft_built_in_show_env(t_env **env);

int		ft_built_in_export_fd(char **str, int fd);
void	ft_show_export_fd(t_env **env, int fd);
void	ft_built_in_show_export_fd(int fd);
void	ft_built_in_show_export(void);
int		ft_export_is_incorrect(char *s);
int		ft_built_in_export(char **str);
void	ft_show_export(t_env **env);
void	ft_putstr_minus_fd(char *s, int len, int fd);

int		ft_built_in_pwd_fd(char **str, int fd);
int		ft_built_in_pwd(char **str);
int		ft_built_in_unset(char **str);

int		exit_bltin(char **args, t_cmd_line **first, pid_t *pid);

int		ft_equal(char *str);
char	*ft_get_home(void);
int		ft_pwd(char *s);
int		ft_built_in_cd(char **str);

int		ft_delete_env(char *str);
void	ft_delete_env_call(t_env **env, char *key);
int		ft_print_error(char *str1, char *str2);
char	*ft_get_str(char *str);
char	*ft_get_str_of_env(t_env **env, char *str);




#endif