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

void	exec_builtin_child(t_cmd *cmd)//, t_data *data
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
    	ft_echo(cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
        printf("hey in child\n");
    else if (ft_strcmp(cmd->args[0], "env") == 0)
        printf("hey in child\n");
}

int	exec_child(t_data *data, int index, char **envp)
{
	t_cmd	*cmd;

	cmd = &data->cmds[index];
	if (cmd->is_builtin)
    {
		exec_builtin_child(cmd);
		exit(EXIT_SUCCESS);
    }
	set_child_fds(data, cmd, index);
	if (!cmd->args || !cmd->args[0])
		exit(EXIT_FAILURE);
	if (!execute_cmd(data, cmd->args, envp))
	{
		// Invalid arg - 2
		// not found 127
		free_all(data);
		/*if (data->mod == 3)
			exit(0);*/
		exit (127);
	}
	exit (EXIT_SUCCESS);
}

int	exec_builtin_parent(t_cmd *cmd)//, t_data *data
{
	//Maybe use exit_code to set EC immediately?
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		//ft_cd();
		printf("hey\n");
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		//ft_export();
		printf("hey\n");
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		//ft_unset();
		printf("hey\n");
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		//ft_exit();
		printf("hey\n");
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
		if (cmd->is_builtin)
			if (!exec_builtin_parent(cmd))
			{
				data->pid[i] = -2;
				continue;
			}
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			return (free_all(data), perror("Fork: "), 0);
		else if (data->pid[i] == 0)
			exec_child(data, i, envp);
	}
	i = -1;
	while (++i < data->cmd_count - 1)
		(close(data->pipes[i][0]), close(data->pipes[i][1]));
	i = -1;
	while (++i < data->cmd_count)
	{
		waitpid(data->pid[i], &status, 0);
		//ADD CONDITION? 
		code = WEXITSTATUS(status);
		/* else if (WIFSIGNALED(status))
			return_exit_code(128 + WTERMSIG(status)); */
	}
	if (WIFEXITED(status))
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

/* int main(int argc, char **argv, char **envp)
{
	t_data data;

	t_input token0 = {"cat", CMD, 0, NULL, NULL};
	t_input token1 = {"test", ARG, 1, NULL, &token0};
	t_input token2 = {"|", PIPE, 2, NULL, &token1};
	t_input token3 = {"grep", CMD, 3, NULL, &token2};
	t_input token4 = {"error", ARG, 4, NULL, &token3};
	t_input token5 = {"|", PIPE, 5, NULL, &token4};
	t_input token6 = {"sort", CMD, 6, NULL, &token5};
	t_input token7 = {"|", PIPE, 7, NULL, &token6};
	t_input token8 = {"uniq", CMD, 8, NULL, &token7};
	t_input token9 = {"|", PIPE, 9, NULL, &token8};
	t_input token10 = {"wc", CMD, 10, NULL, &token9};
	t_input token11 = {"-l", ARG, 11, NULL, &token10};
	t_input token12 = {">", REDIR_OUT, 12, NULL, &token11};
	t_input token13 = {"out2", ARG, 13, NULL, &token12};

	token0.next = &token1;
	token1.next = &token2;
	token2.next = &token3;
	token3.next = &token4;
	token4.next = &token5;
	token5.next = &token6;
	token6.next = &token7;
	token7.next = &token8;
	token8.next = &token9;
	token9.next = &token10;
	token10.next = &token11;
	token11.next = &token12;
	token12.next = &token13;


	memset(&data, 0, sizeof(t_data));
	if (!parse_tokens(&token0, &data))
		return (1);
	//free
	print_cmds(&data);
	if (!create_pipes(&data))
		return (1);
	if (!get_env_path(&data, envp))
		return (1);
	if (!open_files(&data))
		return (1);
	if (!exec_proc(&data, envp))
		return (1);
	free_all(&data);
	return(0);
} */
// TODO 2 outputs for 2 files