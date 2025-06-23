#include "minishell.h"

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
	{
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}

char	*check_path(t_data *data, char *cmd)
{
	char	*path;
	char	*tmp;
	int		i;

	i = -1;
	tmp = NULL;
	while (data->env_path[++i] != NULL)
	{
		if (tmp != NULL)
			free(tmp);
		path = ft_strjoin(data->env_path[i], "/");
		if (!path)
			return (free(tmp), write(2, "Path alloc failed\n", 18), NULL);
		tmp = ft_strjoin(path, cmd);
		free(path);
		if (!tmp)
			return (write(2, "Path alloc failed\n", 18), NULL);
		if (access(tmp, X_OK) == 0)
			return (tmp);
	}
	return (free(tmp), NULL);
}

int	execute_cmd(t_data *data, char **args, char **envp)
{
	char	*path;

	//if () Cond for builtin
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
			return (handle_error(args[0], 2), 0);
	}
	if (execve(path, args, envp) == -1)
	{
		(perror("Execve"), free_all(data));
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

void	exec_builtin_child(t_cmd *cmd, t_data *data)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
    	ft_echo(cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
        ft_pwd();
    else if (ft_strcmp(cmd->args[0], "env") == 0)
		ft_env(data->envp);
}

int	create_hd_filename(char *name, size_t size)
{
	int	hd_id;
	char	*id_str;
	int	fd;

	hd_id = 0;
	while (1)
	{
		id_str = ft_itoa(getpid()); //CHABNGE IT!!!!!!!!!!!!!!!!!!!
		if (!id_str)
			return (0);
		if (ft_strlen("/tmp/heredoc_") + ft_strlen(id_str) + 1 > size) 	//better hidden file
			return (free(id_str), -1);
		ft_strlcpy(name, "/tmp/heredoc_", size), ft_strlcat(name, id_str, size), free(id_str);
		fd = open(name, O_CREAT | O_EXCL | O_RDWR, 0600);
		if (fd != -1)
			return (fd);
		if (hd_id > 10000) // RANDOM!!! RESEARCH??
			break ;
	}
	return (perror ("Open: "), -1);
}

int	set_heredoc_fds(t_cmd *cmd)
{
	char	tmp_name[64];
	int		fd;
	int		i;

	fd = create_hd_filename(tmp_name, sizeof(tmp_name));
	if (fd < 0)
		return (perror("Open heredoc file: "), 0);
	cmd->in = ft_strdup(tmp_name);
	i = -1;
	while (cmd->hd_content && cmd->hd_content[++i])
	{
		write (fd, cmd->hd_content[i], ft_strlen(cmd->hd_content[i]));
		write (fd, "\n", 1);
	}
	close (fd);
	return (1);
}
void	child_handler(int sig)
{
	if (sig == SIGINT)		//crtl C
	{
		printf("\n");
		exit(SIGINT + 128);
	}
	if (sig == SIGQUIT)		//ctrl /
		exit(SIGQUIT + 128);
}

int	exec_child(t_data *data, int index, char **envp)
{
	t_cmd	*cmd;
	int		fd;
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
			if (!set_heredoc_fds(cmd))
				exit(EXIT_FAILURE);
			fd = open(cmd->in, O_RDONLY);
			if (fd < 0)
				perror("Opening heredoc tmp file: "), exit (EXIT_FAILURE);
			dup2(fd, STDIN_FILENO), close(fd), unlink(cmd->in);
		} else
			exit(EXIT_SUCCESS);
	}
	if (cmd->is_builtin)
		exec_builtin_child(cmd, data), exit(EXIT_SUCCESS);
	if (!cmd->args || !cmd->args[0])
		exit(EXIT_FAILURE);
	if (!execute_cmd(data, cmd->args, envp))
		free_all(data),	exit (127);
	exit (EXIT_SUCCESS);
}

int	exec_builtin_parent(t_cmd *cmd, t_data *data)
{
	//Maybe use exit_code to set EC immediately?
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		ft_cd(data, cmd);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		ft_export(data, cmd);
		//printf("hey\n");
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		ft_unset(data, cmd);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		ft_exit(data, cmd);
	else
		return (1);
	return (0);
}

int	exec_proc(t_data *data, char **envp)
{
	int	i;
	int	status;
	int code;
	t_cmd *cmd;

	data->pid = malloc(sizeof(pid_t) * data->cmd_count);
	if (!data->pid)
		return (perror("PID malloc: "), free_all(data), 0);
	i = -1;
	while (++i < data->cmd_count)
	{
		cmd = &data->cmds[i];
		if (cmd->error_skip)
		{
			data->pid[i] = -2;
			continue;
		}
		if (cmd->is_builtin)
			if (!exec_builtin_parent(cmd, data))
			{
				data->pid[i] = -2;
				continue;
			}
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			return (free_all(data), perror("Fork: "), 0);
		else if (data->pid[i] == 0)
			exec_child(data, i, envp);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	i = -1;
	while (++i < data->cmd_count - 1)
		(close(data->pipes[i][0]), close(data->pipes[i][1]));
	i = -1;
	while (++i < data->cmd_count)
	{
		/* if (data->pid[i] == -2 || data->pid[i] == -1)
			continue; */
		waitpid(data->pid[i], &status, 0);
		//ADD CONDITION? 
		code = WEXITSTATUS(status);
		/* else if (WIFSIGNALED(status))
			return_exit_code(128 + WTERMSIG(status)); */
		if(WIFSIGNALED(status))
		{
			int sig = WTERMSIG(status);
			if (sig == SIGINT)
			{
				write(1, "\n", 1);
				return_exit_code(SIGINT + 128);
			//	return_sig_flag(2);
			}
			if (sig == SIGQUIT)
			{
				write(2, "Quit (core dumped)\n", 20);
				return_exit_code(SIGQUIT + 128);
			//	return_sig_flag(3);
			}	
		}
	}
	if (/* data->pid[i] == 0 && */ WIFEXITED(status))
		{
			if (code != 0)
				return_exit_code(/* WEXITSTATUS(status) */code);
		}
	return (free_all(data), 1);
}

int	create_pipes(t_data *data)
{
	int	i;

	if (data->cmd_count < 2)
		return (1);
	data->pipes = ft_calloc(sizeof(int *), (data->cmd_count));
	if (!data->pipes)
		return (perror("Pipes memory alloc: "), free_all(data), 0);
	i = -1;
	while (++i < data->cmd_count - 1)
	{
		data->pipes[i] = ft_calloc(sizeof(int), 2);
		if (!data->pipes[i] || pipe(data->pipes[i]) == -1)
			return (free_all(data), perror("Pipe: "), 0);
	}
	data->pipes[i] = NULL;
	return (1);
}
