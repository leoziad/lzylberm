#include "minishell.h"

void	signal_handler_2(int sig)
{
	exit_status += sig;
	if (sig == 2)
	{
		exit_status = 130;
		printf("\n");
//		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/* Compares the argument string with the name of built-ins, and calls the correct one.
*/
int	ft_exec_bd_fd(char *str, char **args, t_cmd_line **cmd_line, pid_t *pid)
{
	if (str == NULL)
		return (0);
	if (!ft_strcmp("exit", str))
	{
		exit_bltin(args, cmd_line, pid);
		return (1);
	}
	if (!ft_strcmp("cd", str))
		ft_built_in_cd(args);
	else if (!ft_strcmp("echo", str))
		ft_built_in_echo_fd(args, (*cmd_line)->fd_out);
	else if (!ft_strcmp("env", str))
		ft_built_in_env_fd(args, (*cmd_line)->fd_out);
	else if (!ft_strcmp("pwd", str))
		ft_built_in_pwd_fd(args, (*cmd_line)->fd_out);
	else if (!ft_strcmp("export", str))
		ft_built_in_export_fd(args, (*cmd_line)->fd_out);
	else if (!ft_strcmp("unset", str))
		ft_built_in_unset(args);
	return (0);
}

int	no_forking(t_cmd_line **cmd, pid_t *pid)
{
	if ((*cmd)->argv == NULL)
		return (0);
	else if (ft_exec_bd_fd((*cmd)->argv[0],
			(*cmd)->argv, cmd, pid) != 0)
	{
		return (0);
	}
	return (0);
}

/* Concatenates the argument string and a possible path to try.
*/
char	*get_acces(char *str, char *path)
{
	char	*back_slash;
	char	*new;

	back_slash = ft_strjoin(path, "/");
	if (back_slash == NULL)
		return (NULL);
	new = ft_strjoin(back_slash, str);
	free(back_slash);
	if (new == NULL)
		return (NULL);
	return (new);
}

/* Try to get access to execute the command's argument with a possible path.
*/
int	try_acces(char *str, char *path)
{
	char	*try;

	try = get_acces(str, path);
	if (try == NULL)
		return (50);
	if (access(try, X_OK) == 0)
	{
		free(try);
		return (1);
	}
	free(try);
	return (0);
}

/* Get the PATH variable from the environment, and check every possible path for the command's argument.
*/
char	*get_bin_argv_zero(char *str, char *path, int i)
{
	int		ret;
	char	**split_path;
	char	*try;

	if (str && (str[0] == '.' || str[0] == '/'))
		return (str);
	split_path = ft_split(path, ':');
	if (split_path == NULL)
		return (write_bad_cmd_free(str));
	while (split_path[i] && str[0] != '\0')
	{
		ret = try_acces(str, split_path[i]);
		if (ret == 1)
		{
			try = get_acces(str, split_path[i]);
			free_split(split_path);
			return (try);
		}
		if (ret == 50)
			return (free_split_ret_null(split_path));
		i++;
	}
	write_bad_cmd_free_split(str, split_path);
	exit_status = 127;
	return (str);
}

int	exec_builtin(char **str, t_cmd_line **cmdl, pid_t *pid)
{
	free(str);
	if (ft_exec_builtin((*cmdl)->argv[0], (*cmdl)->argv, cmdl, pid) == 2)
		exit(1);
	exit(0);
	return (0);
}

/* Executes the command.
   If execution fails : verify permission for the command's argument, set the exit status
   and clean everything.
*/
int	ft_exec_cmd(t_cmd_line **cmdl, char **str, pid_t *pid)
{
	struct stat	buff;

	execve((*cmdl)->argv[0], (*cmdl)->argv, str);
	if (stat((*cmdl)->argv[0], &buff) == 0)
	{
		write(2, "minishell: ", ft_strlen("minishell: "));
		write(2, (*cmdl)->argv[0], ft_strlen((*cmdl)->argv[0]));
		write(2, ": Permission denied\n", ft_strlen(": Permission denied\n"));
		exit(126);
	}
	free_all(cmdl);
	free(str);
	free(pid);
	ft_clean_env();
	exit_status = 127;
	exit(exit_status);
	return (0);
}

/* Set the STDIN and STDOUT of the command to point to the appropriate file descriptors.
   Obtain an array of environment variable strings from the environment chained list.
   If the command is not a buit-in, add the correct path to the name of the executable that
   constitutes the command's argument.
   Execute the command.
*/
int	ft_execve_fct(t_cmd_line **cmd, t_cmd_line **cmd_line, pid_t *pid)
{
	char		**str;

	dup2((*cmd)->fd_in, STDIN_FILENO);
	dup2((*cmd)->fd_out, STDOUT_FILENO);
	close_fd_all(cmd);
	str = get_env_tab(get_env_adress());
	if (str == NULL)
		free_fd_all_exit_malloc_error(cmd_line);
	if (ft_is_builtin((*cmd)->argv[0]) == 0)
	{
		if ((*cmd)->argv[0] == NULL)
			free_str_fd_all_env_pid_exit(cmd, pid, str);
		(*cmd)->argv[0] = get_bin_argv_zero((*cmd)->argv[0],
				get_env_var("PATH"), 0);
	}
	if ((*cmd)->argv[0] == NULL)
		free_str_fd_exit_malloc_error(str, cmd_line);
	free_file_name((*cmd)->name_file);
	if ((*cmd)->fd_in < 0 || (*cmd)->fd_out < 0)
		free_str_fd_all_env_pid_exit(cmd_line, pid, str);
	if (ft_is_builtin((*cmd)->argv[0]))
		exec_builtin(str, cmd, pid);
	else
		ft_exec_cmd(cmd, str, pid);
	return (0);
}

/* Creates a child process for the current command and starts execution.
   If the command's input fd is different from STDIN or output fd from STDOUT,
   closes them.
*/
int	multi_fork(pid_t *pid, int i, t_cmd_line **cmd_line, t_cmd_line **cur_c)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid[i] = fork();
	if (pid[i] == -1)
		exit(1);
	if (pid[i] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		ft_execve_fct(cur_c, cmd_line, pid);
	}
	if ((*cur_c)->fd_in != 0)
		close((*cur_c)->fd_in);
	if ((*cur_c)->fd_out != 1)
		close((*cur_c)->fd_out);
	return (0);
}

/* If there is only one command and it's a built-in, executes it.
   Else, creates a child process for every command.
*/
int	forking(t_cmd_line **cmd_line, pid_t *pid)
{
	int			nb_cmd;
	int			i;
	t_cmd_line	*cur_c;
	t_cmd_line	*tmp;

	i = 0;
	cur_c = *cmd_line;
	nb_cmd = get_nbr_cmd(cur_c);
	while (cur_c)
	{
		open_fd(&cur_c);
		cur_c = cur_c->next;
	}
	cur_c = *cmd_line;
	if (nb_cmd == 1 && ft_is_builtin(cur_c->argv[0]))
	{
		return (no_forking(cmd_line, pid));
	}
	tmp = *cmd_line;
	while (tmp)
	{
		tmp = tmp->next;
	}
	while (i < nb_cmd)
	{
		multi_fork(pid, i, cmd_line, &cur_c);
		cur_c = cur_c->next;
		i++;
	}
	return (0);
}

/* If children precesses were created, waits for each of them to finish execution.
   Sets the exit status to the correct value whether the child returned due to a signal
   or because it executed completely.
*/
int	wait_pid(t_cmd_line **cmdl, pid_t *pid)
{
	t_cmd_line	*cur_c;
	int			nb_cmd;
	int			i;

	i = 0;
	cur_c = *cmdl;
	nb_cmd = get_nbr_cmd(cur_c);
	if (nb_cmd == 1 && ft_is_builtin((*cmdl)->argv[0]))
	{
		return (0);
	}
	while (i < nb_cmd)
	{
		waitpid(pid[i], &exit_status, 0);
		if (WIFEXITED(exit_status))
			exit_status = WEXITSTATUS(exit_status);
		else if (WIFSIGNALED(exit_status))
			exit_status = 128 + WTERMSIG(exit_status);
		i++;
	}
	return (0);
}

/* Builds the command pipeline by connecting each command's output to the next command's input.
   Allocates an array of pid_t to store each child process' pid in case of forking.
   Redefines the signal handlers for when the parent is waiting for the children, and then
   for when they have all finished execution.
*/
int	execute(t_cmd_line **cmd_line)
{
	t_cmd_line	*cur_c;
	pid_t		*pid;
	int			ret;

	cur_c = *cmd_line;
	ret = init_pipes(cmd_line);
	if (ret != 0)
		return (ret);
	pid = malloc(sizeof(pid_t) * get_nbr_cmd(cur_c));
	if (pid == NULL)
		return (50);
	forking(cmd_line, pid);
	signal(SIGINT, signal_handler_2);
	signal(SIGQUIT, SIG_IGN);
	wait_pid(cmd_line, pid);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	free(pid);
	return (0);
}

static char	*expanded_str(t_token **cur_t, char *str)
{
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			new = variable_expansion(cur_t, str, new, &i);
			if (new == NULL)
				return (NULL);
		}
		else
		{
			new = regular_expansion(str, &i, new);
			if (new == NULL)
				return (NULL);
		}
	}
	free(str);
	return (new);
}

/* Display a prompt. Read STDIN and write its content to the here-doc's fd until you read
   a line containing only the delimiter.
*/
int	write_in_fd(int fd, t_token **cur_t)
{
	char	*str;

	while (1)
	{
		str = readline(">");
		if (str == NULL)
			return (45);
		if (ft_strcmp((*cur_t)->str, str) == 0)
			break ;
		if (str[0] != '\0')
		{
			if ((*cur_t)->expanded == 0)
			{
				str = expanded_str(cur_t, str);
				if (str == NULL)
					return (50);
			}
		}
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	free(str);
	return (0);
}

int	aleatori_char(void)
{
	char	buff[4];
	int		nbr;
	int		fd;

	fd = open("/dev/random", O_RDONLY);
	if (fd < -1)
		return (-1);
	read(fd, buff, 4);
	nbr = *(int *)buff;
	if (nbr < 0)
		nbr++;
	if (nbr < 0)
		nbr = nbr * (-1);
	return ('a' + nbr % 26);
}

/* Create a random name for the here-doc
*/

char	*random_name(void)
{
	char	*name_file;
	int		i;

	i = 0;
	name_file = malloc(sizeof(char) * 11);
	name_file[10] = '\0';
	while (i < 10)
	{
		name_file[i] = (char)aleatori_char();
		i++;
	}
	return (name_file);
}

/* Create a here-document.
   Generate a random name and try to create/open the corresponding file until it works.
   Read STDIN and write its content to the here-doc until you read the delimiter.
   Assign the here-doc's fd as the current command's input fd.
   If a file was previously associated with the command, unlink it and change it to the here-doc.
*/
int	create_heredoc_fd(t_cmd_line **cmdl, t_token **cur_t)
{
	int		fd;
	char	*name_file;

	name_file = NULL;
	fd = -1;
	while (fd == -1)
	{
		if (name_file)
			free(name_file);
		name_file = random_name();
		fd = open(name_file, O_CREAT | O_EXCL | O_RDWR, 0644);
	}
	write_in_fd(fd, cur_t);
	fd = open(name_file, O_RDONLY);
	(*cmdl)->fd_in = fd;
	if ((*cmdl)->name_file != NULL)
	{
		unlink((*cmdl)->name_file);
		free((*cmdl)->name_file);
	}
	(*cmdl)->name_file = name_file;
	return (fd);
}