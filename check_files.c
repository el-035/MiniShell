#include "minishell.h"

static void	add_skip_flag(t_cmd *cmd, int i, int cmd_count, int mode)
{
	cmd->error_skip = 1;
	if (mode == 1)
	{
		if (i == cmd_count - 1)
			return_exit_code(1);		
	}
	else
	{
		if (i == cmd_count - 1)
			return_exit_code(0);
	}
}

static int	check_permission(t_data *data, int i, int file_order)
{
	if (file_order == 1)
	{
		if (access(data->cmds[i].in, F_OK) != -1)
		{
			if (access(data->cmds[i].in, R_OK) == -1)
				return (handle_error(data->cmds[i].in, 1), add_skip_flag(&data->cmds[i], i, data->cmd_count, 1), 0);
		}
		else
		{
			handle_error(data->cmds[i].in, 0);
			return (add_skip_flag(&data->cmds[i], i, data->cmd_count, 1), 0);
		}
	}
	else if (access(data->cmds[i].out, F_OK) != -1)
		if (access(data->cmds[i].out, R_OK) == -1 || access(data->cmds[i].out, W_OK) == -1)
			return (handle_error(data->cmds[i].out, 1), 0);
	return (1);
}

static int	get_open_flags(int append)
{
	int	flags;

	flags = O_CREAT | O_WRONLY;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	return (flags);
}

static int	check_fd(t_data *data, int i, char *file, int mode)
{
	int	flags;

	if (mode == 1)
	{
		if (!check_permission(data, i, 1))
			return (0);
		data->fd1 = open(file, O_RDONLY);
		if (data->fd1 == -1)
			return (add_skip_flag(&data->cmds[i], i, data->cmd_count, 1), handle_error(file, 0), 0);
	}
	else
	{
		if (!check_permission(data, i, 2))
			return (0);
		flags = get_open_flags(data->cmds[i].append);
		data->fd2 = open(file, flags, 0666);
		if (data->fd2 == -1)
			return (add_skip_flag(&data->cmds[i], i, data->cmd_count, 1), handle_error(file, 0), 0);
	}
	return (1);
}

int	open_files(t_data *data)
{
	t_cmd	*cmd;
	int		i;

	i = -1;
	while (++i < data->cmd_count)
	{
		cmd = &data->cmds[i];
		if (!cmd->args || !cmd->args[0])
			add_skip_flag(cmd, i, data->cmd_count, 2);
		if (cmd->in)
		{
			if (!check_fd(data, i, cmd->in, 1))
				continue ;
		}
		if (cmd->out)
		{
			if (!check_fd(data, i, cmd->out, 2))
				continue ;
		}
	}
	return (1);
}
