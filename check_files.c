#include "minishell.h"

static void	add_skip_flag(t_cmd *cmd, int i, int cmd_count)
{
	cmd->error_skip = 1;
	if (i == cmd_count - 1)
		return_exit_code(1);
}

static int	check_permission(t_data *data, int i, int file_order)
{
	if (file_order == 1)
	{
		if (access(data->cmds[i].in, F_OK) != -1)
		{
			if (access(data->cmds[i].in, R_OK) == -1)
				return (handle_error(data->cmds[i].in, 1), add_skip_flag(&data->cmds[i], i, data->cmd_count), 0);
		}
		else
		{
			handle_error(data->cmds[i].in, 0);
			return (add_skip_flag(&data->cmds[i], i, data->cmd_count), 0);
		}
	}
	else if (access(data->cmds[i].out, F_OK) != -1)
		if (access(data->cmds[i].out, R_OK) == -1 || access(data->cmds[i].out, W_OK) == -1)
			return (handle_error(data->cmds[i].out, 1), 0);
	return (1);
}

int	get_env_path(t_data *data, char **envp)
{
	int	cmp;
	int	i;

	i = -1;
	while (envp[++i])
	{
		cmp = ft_strncmp(envp[i], "PATH=", 5);
		if (cmp == 0)
		{
			data->env_path = ft_split(envp[i] + 5, ':');
			break ;
		}
	}
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

int	open_files(t_data *data)
{
	t_cmd	*cmd;
	int		flags;
	int		i;

	i = -1;
	while (++i < data->cmd_count)
	{
		cmd = &data->cmds[i];
		if (cmd->in)
		{
			if (!check_permission(data, i, 1))
				continue ;
			data->fd1 = open(cmd->in, O_RDONLY);
			if (data->fd1 == -1)
			{
				(add_skip_flag(cmd, i, data->cmd_count), handle_error(cmd->in, 0));
				continue ;
			}
		}
		if (cmd->out)
		{
			if (!check_permission(data, i, 2))
				continue ;
			flags = get_open_flags(cmd->append);
			data->fd2 = open(cmd->out, flags, 0666);
			if (data->fd2 == -1)
			{
				add_skip_flag(cmd, i, data->cmd_count), handle_error(cmd->out, 0);
				continue ;
			}
		}
	}
	return (1);
}
