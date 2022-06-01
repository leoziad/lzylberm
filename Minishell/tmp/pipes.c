#include "minishell.h"

int	get_nbr_cmd(t_cmd_line *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

void	free_fd_tab(int **in_out_tab)
{
	int	i;

	i = 0;
	while (in_out_tab[i])
	{
		free(in_out_tab[i]);
		i++;
	}
	free(in_out_tab);
}

/* Allocates an array of int pairs, each pair being the input fd and
   output fd for a command (obtained from the pipe function).
   Sets STDIN as the first command's input, then connects each command's
   output to the next command's input. Finally, sets STDOUT as the output
   fot the last command in the pipeline.
*/
int	connect_pipes(int **in_out_tab, int i, t_cmd_line *cur_c)
{
	in_out_tab[i] = malloc(sizeof(int) * (2));
	if (in_out_tab[i] == NULL)
		return (50);
	if (pipe(in_out_tab[i]) == -1)
		return (40);
	if (i == 0)
		cur_c->fd_in = 0;
	else
		cur_c->fd_in = in_out_tab[i - 1][0];
	if (cur_c->next == NULL)
	{
		close(in_out_tab[i][0]);
		close(in_out_tab[i][1]);
		cur_c->fd_out = 1;
	}
	else
		cur_c->fd_out = in_out_tab[i][1];
	return (0);
}

/* Creates the pipeline of commands.
*/
int	init_pipes(t_cmd_line **cmd_line)
{
	t_cmd_line	*cur_c;
	int			**in_out_tab;
	int			i;
	int			ret;

	i = 0;
	cur_c = *cmd_line;
	in_out_tab = malloc(sizeof(int *) * (get_nbr_cmd(cur_c) + 1));
	if (in_out_tab == NULL)
		return (50);
	in_out_tab[get_nbr_cmd(cur_c)] = NULL;
	while (cur_c)
	{
		ret = connect_pipes(in_out_tab, i, cur_c);
		if (ret != 0)
		{
			free_fd_tab(in_out_tab);
			return (ret);
		}
		cur_c = cur_c->next;
		i++;
	}
	free_fd_tab(in_out_tab);
	return (0);
}

/* In case of input redirection, opens the file that needs to be read
   from with the appropriate flags.
   In case a here-document is needed, creates it and assigns its fd as the command's input fd.
*/
int	redirect_file_in(t_cmd_line **cmd_line, t_token *cur_t, t_e_token type)
{
	if (type == FILE_IN)
	{
		if ((*cmd_line)->fd_in != 0)
			close((*cmd_line)->fd_in);
		(*cmd_line)->fd_in = open(cur_t->str, O_RDONLY);
		if ((*cmd_line)->fd_in == -1)
		{
			write(1, "minishell: ", 11);
			perror(cur_t->str);
			return (-1);
		}
	}
	else if (type == DELIMITER)
	{
		if ((*cmd_line)->fd_in != 0)
			close((*cmd_line)->fd_in);
		(*cmd_line)->fd_in = create_heredoc_fd(cmd_line, &cur_t);
		if ((*cmd_line)->fd_in == -1)
			return (-1);
	}
	return (0);
}

/* In case of output redirection, opens the file that needs to be written
   to with the appropriate flags.
   O_CREAT => if file doesn't exist, create it.
   O_TRUNC => if it exists, go to start.
   O_APPEND => if it exists, go to end.
   0644 => t_mode signifying read/write, read, read permissions
*/
int	redirect_file_out(t_cmd_line **cmd_line, t_token *cur_t, t_e_token type)
{
	if (type == FILE_OUT)
	{
		if ((*cmd_line)->fd_out != 1)
			close((*cmd_line)->fd_out);
		(*cmd_line)->fd_out = open(cur_t->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if ((*cmd_line)->fd_out == -1)
			return (-1);
	}
	else if (type == FILE_OUT_OVER)
	{
		if ((*cmd_line)->fd_out != 1)
			close((*cmd_line)->fd_out);
		(*cmd_line)->fd_out = open(cur_t->str, O_CREAT | O_RDWR | O_APPEND, 0644);
		if ((*cmd_line)->fd_out == -1)
			return (-1);
	}
	return (0);
}

/* In case of a redirection, the fd for the input/output of the command
   needs to be changed. It is obtained by opening the file that needs to
   be written to/read from.
*/
int	open_fd(t_cmd_line **cmd_line)
{
	t_token	*cur_t;

	cur_t = (*cmd_line)->tokens;
	while (cur_t)
	{
		if (cur_t->type == FILE_IN || cur_t->type == DELIMITER)
			if (redirect_file_in(cmd_line, cur_t, cur_t->type) == -1)
				return (-1);
		if (cur_t->type == FILE_OUT || cur_t->type == FILE_OUT_OVER)
			if (redirect_file_out(cmd_line, cur_t, cur_t->type) == -1)
				return (-1);
		cur_t = cur_t->next;
	}
	return (0);
}

/* Close all fd previously associated with a command's input and output,
   as long as they are not STDIN or STDOUT.
*/
void	close_fd_all(t_cmd_line **cmd_line)
{
	t_cmd_line	*cur_c;

	cur_c = *cmd_line;
	while (cur_c)
	{
		if (cur_c->fd_in != 0)
			close(cur_c->fd_in);
		if (cur_c->fd_out != 1)
			close(cur_c->fd_out);
		cur_c = cur_c->next;
	}
}