#include "minishell.h"

int	check_permission(t_data *data, char *fd_name, int file_order)
{
	if (file_order == 1)
	{
		if (access(fd_name, F_OK) != -1)
		{
			if (access(fd_name, R_OK) == -1)
				return (handle_error(fd_name, 1), 0);
		}
		else
		{
			handle_error(fd_name, 0);
			return (0);
		}
	}
	else if (access(fd_name, F_OK) != -1)
		if (access(fd_name, R_OK) == -1 || access(fd_name, W_OK) == -1)
			return (handle_error(fd_name, 1), 0);
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

void	add_skip_flag(t_cmd *cmd)
{
	cmd->error_skip = 1;
}

int	get_open_flags(int append)
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
	t_cmd	*first;
	t_cmd	*last;
	int		flags;

	first = &data->cmds[0];
	last = &data->cmds[data->cmd_count - 1];
	if (first->in)
	{
		if (!check_permission(data, first->in, 1))
			return (add_skip_flag(first), 0);
		data->fd1 = open(first->in, O_RDONLY);
		if (data->fd1 == -1)
			return (add_skip_flag(first), handle_error(first->in, 0), 0);
	}
	if (last->out)
	{
		if (!check_permission(data, last->out, 2))
			return (add_skip_flag(last), 0);
		flags = get_open_flags(last->append);
		data->fd2 = open(last->out, flags, 0666);
		if (data->fd2 == -1)
			return (add_skip_flag(last), handle_error(last->out, 0), 0);
	}
	return (1);
}
