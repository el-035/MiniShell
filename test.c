#include "minishell.h"

/* static int	count_cmds(t_input *tokens, t_data *data)
{
	t_input	*cur;

	cur = tokens;
	data->cmd_count = 1;
	while (cur)
	{
		if (cur->type == PIPE)
			data->cmd_count++;
		cur = cur->next;
	}
	data->cmds = ft_calloc(data->cmd_count, sizeof(t_cmd));
	if (!data->cmds)
		return (perror("Malloc: "), 0);
	return (1);
}

static int	count_args(t_input *cur)
{
	int		argc;
	t_input	*tmp;

	argc = 0;
	tmp = cur;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CMD || tmp->type == ARG)
			argc++;
		tmp = tmp->next;
	}
	return (argc);
}

int	exec_parse(t_input *cur, t_cmd *cmd)
{
	int	j;

	j = 0;
	while (cur && cur->type != PIPE)
	{
		if ((cur->type == CMD || cur->type == ARG) && (!cur->prev
				|| (cur->prev->type != REDIR_IN && cur->prev->type != REDIR_OUT
					&& cur->prev->type != REDIR_APPEND)))
			cmd->args[j++] = ft_strdup(cur->content);
		else if (cur->type == REDIR_IN && cur->next)
		{
			cmd->in = ft_strdup(cur->next->content);
			cur = cur->next;
		}
		else if ((cur->type == REDIR_OUT || cur->type == REDIR_APPEND)
			&& cur->next)
		{
			cmd->out = ft_strdup(cur->next->content);
			cmd->append = (cur->type == REDIR_APPEND);
			cur = cur->next;
		}
		cur = cur->next;
	}
	cmd->args[j] = NULL;
	return (1);
}

int	parse_tokens(t_input *tokens, t_data *data)
{
	int		i;
	int		j;
	t_input	*cur;
	t_cmd	*cmd;

	i = -1;
	cur = tokens;
	if (!count_cmds(tokens, data))
		return (0);
	while (cur && ++i < data->cmd_count)
	{
		cmd = &data->cmds[i];
		cmd->args = ft_calloc(count_args(cur) + 1, sizeof(char *));
		if (!cmd->args)
			return (perror("Malloc: "), free_all(data), 0);
		if (!exec_parse(cur, cmd))
			return (free_all(data), 0);
		if (cur && cur->type == PIPE)
			cur = cur->next;
	}
	return (1);
} */














































#include "minishell.h"

static char	*check_path(t_data *data, char *cmd)
{
	char	*path;
	char	*tmp;
	int		i;

	i = -1;
	tmp = NULL;
	if (!data->env_path)
		return (handle_error(cmd, 0), NULL);
	while (data->env_path[++i] != NULL)
	{
		if (tmp != NULL)
			free(tmp);
		path = ft_strjoin(data->env_path[i], "/");
		if (!path)
			return (free(tmp), fail_mall(), NULL);
		tmp = ft_strjoin(path, cmd);
		free(path);
		if (!tmp)
			return (fail_mall(), NULL);
		if (access(tmp, X_OK) == 0)
			return (tmp);
	}
	return (free(tmp), handle_error(cmd, 2), NULL);
}

static int	execute_cmd(t_data *data, char **args, char **envp)
{
	char	*path;

	// if () Cond for builtin
	if (args[0][0] == '/' || (args[0][0] == '.' && args[0][1] == '/'))
	{
		if (access(args[0], X_OK) == 0)
			path = args[0];
		else
			return (handle_error(args[0], 0), 0);
	}
	else
	{
		path = check_path(data, args[0]);
		if (!path)
			return (return_exit_code(1), 0);
	}
	if (execve(path, args, envp) == -1)
	{
		if (path != args[0])
			free(path);
		exit(127);
	}
	if (path != args[0])
		free(path);
	return (1);
}

static void	set_child_fds(t_data *data, t_cmd *cmd, int index)
{
	int	i;

	if (cmd->in)
		dup2(data->fd1, STDIN_FILENO);
	else if (index > 0)
		dup2(data->pipes[index - 1][0], STDIN_FILENO);
	if (cmd->out)
		dup2(data->fd2, STDOUT_FILENO);
	else if (index < data->cmd_count - 1)
		dup2(data->pipes[index][1], STDOUT_FILENO);
	i = -1;
	while (++i < data->cmd_count - 1)
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
	}
	if (cmd->in == NULL && data->fd1 != STDIN_FILENO && data->fd1 != -1)
		close(data->fd1);
	if (cmd->out == NULL && data->fd2 != STDOUT_FILENO && data->fd2 != -1)
		close(data->fd2);
}

int	exec_child(t_data *data, int index, char **envp)
{
	t_cmd				*cmd;
	int					fd;
	struct sigaction	sig;

	sig.sa_handler = &child_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
	cmd = &data->cmds[index];
	set_child_fds(data, cmd, index);
	if (cmd->is_hd == 1)
	{
		if (cmd->hd_content)
		{
			if (!set_heredoc_fds(cmd, index))
				exit(EXIT_FAILURE);
			fd = open(cmd->in, O_RDONLY);
			if (fd < 0)
				(perror("Opening heredoc tmp file: "), exit(EXIT_FAILURE));
			(dup2(fd, STDIN_FILENO), close(fd), unlink(cmd->in));
		}
		else
			exit(EXIT_SUCCESS);
	}
	if (cmd->is_builtin)
		(exec_builtin_child(cmd, data), exit(EXIT_SUCCESS));
	if (!cmd->args || !cmd->args[0])
		exit(EXIT_FAILURE);
	if (!execute_cmd(data, cmd->args, envp))
		(free_all(data), exit(127)); //free_cmd USE INSTEAD!!!!!!!!!!!!!1
	exit(EXIT_SUCCESS);
}