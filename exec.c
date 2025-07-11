/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <efittant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 00:54:42 by apchelni          #+#    #+#             */
/*   Updated: 2025/07/07 21:15:47 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_proc(t_data *data, int *status, int *code)
{
	int	i;
	int	sig;

	i = -1;
	while (++i < data->cmd_count)
	{
		if (data->pid[i] != -2)
			waitpid(data->pid[i], status, 0);
		if (WIFEXITED(*status))
			*code = WEXITSTATUS(*status);
		if (WIFSIGNALED(*status))
		{
			sig = WTERMSIG(*status);
			if (sig == SIGINT)
				(write(1, "\n", 1), return_exit_code(SIGINT + 128));
			if (sig == SIGQUIT)
				(write(2, "Quit (core dumped)\n", 20), return_exit_code(SIGQUIT
						+ 128));
		}
	}
}

static int	exec(t_data *data, char **envp, int i)
{
	while (++i < data->cmd_count)
	{
		if (i < data->cmd_count - 1)
		{
			if (pipe(data->pipes[1]) == -1)
				return (perror("Pipe"), 0);
		}
		else
		{
			data->pipes[1][0] = -1;
			data->pipes[1][1] = -1;
		}
		if (data->cmds[i].error_skip)
		{
			data->pid[i] = -2;
			if (data->pipes[1][0] != -1)
				close(data->pipes[1][0]);
			if (data->pipes[1][1] != -1)
				close(data->pipes[1][1]);
			continue ;
		}
		if (data->cmds[i].is_builtin)
		{
			if (!exec_builtin_parent(&data->cmds[i], data))
			{
				data->pid[i] = -2;
				if (data->pipes[1][0] != -1) 
					close(data->pipes[1][0]);
				if (data->pipes[1][1] != -1) 
					close(data->pipes[1][1]);
				continue ;
			}
		}
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			return (perror("Fork"), 0);
		else if (data->pid[i] == 0)
			exec_child(data, i, envp);
		(signal(SIGINT, SIG_IGN), signal(SIGQUIT, SIG_IGN));
		if (data->pipes[0][0] != -1)
			close (data->pipes[0][0]);
		if (data->pipes[0][1] != -1)
			close (data->pipes[0][1]);
		data->pipes[0][0] = data->pipes[1][0];
		data->pipes[0][1] = data->pipes[1][1];
	}
	return (1);
}

int	exec_proc(t_data *data, char **envp)
{
	int	status;
	int	code;

	status = 0;
	data->pid = malloc(sizeof(pid_t) * data->cmd_count);
	if (!data->pid)
		return (perror("PID: "), 0);
	if (!exec(data, envp, -1))
		return (0);
	if (data->pipes[0][0] != -1)
		close(data->pipes[0][0]);
	if (data->pipes[0][1] != -1)
		close(data->pipes[0][1]);
	if (data->pipes[1][0] != -1)
		close(data->pipes[1][0]);
	if (data->pipes[1][1] != -1)
		close(data->pipes[1][1]);
	wait_proc(data, &status, &code);
	if (WIFEXITED(status))
		if (code != 0)
			return_exit_code(code);
	return (1);
}

/* int	create_pipes(t_data *data)
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
} */
