#include "minishell.h"

int	exec_proc(t_data *data, char **envp)
{
	int				i;
	int				status;
	int				code;
	t_cmd			*cmd;

	status = 0;
	data->pid = malloc(sizeof(pid_t) * data->cmd_count);
	if (!data->pid)
		return (perror("PID malloc: "), 0);
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
			return (perror("Fork: "), 0);
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
		if (data->pid[i] != -2)
			waitpid(data->pid[i], &status, 0);
		code = WEXITSTATUS(status);
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
	if (WIFEXITED(status))
		{
			if (code != 0)
				return_exit_code(code);
		}
	return (1);
}

int	create_pipes(t_data *data)
{
	int	i;

	if (data->cmd_count < 2)
		return (1);
	data->pipes = ft_calloc(sizeof(int *), (data->cmd_count));
	if (!data->pipes)
		return (perror("Pipes memory alloc: "), 0);
	i = -1;
	while (++i < data->cmd_count - 1)
	{
		data->pipes[i] = ft_calloc(sizeof(int), 2);
		if (!data->pipes[i] || pipe(data->pipes[i]) == -1)
			return (perror("Pipe: "), 0);
	}
	data->pipes[i] = NULL;
	return (1);
}
