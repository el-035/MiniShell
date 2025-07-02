#include "minishell.h"

static char	*check_path(t_data *data, char *cmd)
{
	char	*path;
	char	*tmp;
	int		i;

	i = -1;
	tmp = NULL;
	if (!cmd || *cmd == '\0')
		return (handle_error(cmd, 2), NULL);
	if (data->env_path && *data->env_path && cmd && *cmd)
		while (data->env_path[++i] != NULL)
		{
			if (tmp != NULL)
				free(tmp);
			path = ft_strjoin(data->env_path[i], "/");
			if (!path)
				return (fail_mall(), NULL);
			tmp = ft_strjoin(path, cmd);
			free(path);
			if (!tmp)
				return (fail_mall(), NULL);
			if (access(tmp, X_OK) == 0)
				return (tmp);
		}
	else
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
			else
				return (handle_error(cmd, 0), NULL);
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
	if (index < data->cmd_count - 1)
			dup2(data->pipes[index][1], STDOUT_FILENO);
	i = -1;
	while (++i < data->cmd_count - 1)
	{
		if (data->pipes)
			(close(data->pipes[i][0]), close(data->pipes[i][1]));
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
				(free_split(data->envp), free_all(data),exit(EXIT_FAILURE));
			fd = open(cmd->in, O_RDONLY);
			if (fd < 0)
				(perror("Opening heredoc tmp file: "), free_split(data->envp), free_all(data), exit(EXIT_FAILURE));
			(dup2(fd, STDIN_FILENO), close(fd), unlink(cmd->in));
		}
		else
			(free_split(data->envp), free_all(data), exit(EXIT_SUCCESS));
	}
	if (cmd->is_builtin)
		(exec_builtin_child(cmd, data), free_split(data->envp), free_all(data), exit(EXIT_SUCCESS));
	if (!cmd->args || !cmd->args[0])
	{
		if (cmd->is_hd == 1)
			(free_split(data->envp), free_all(data), exit(EXIT_SUCCESS));
		else
			(free_split(data->envp), free_all(data), exit(EXIT_FAILURE));
	}
	if (!execute_cmd(data, cmd->args, envp))
		(free_split(data->envp), free_all(data), exit(127)); //free_cmd USE INSTEAD!!!!!!!!!!!!!1
	(free_split(data->envp), free_all(data), exit(EXIT_SUCCESS));
}
