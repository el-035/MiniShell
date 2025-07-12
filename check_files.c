/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <apchelni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 00:54:42 by apchelni          #+#    #+#             */
/*   Updated: 2025/07/12 03:22:07 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_skip_flag(t_cmd *cmd)
{
	cmd->error_skip = 1;
}

static int	check_permission(t_data *data, char *file, int i, int file_order)
{
	struct stat	sb;

	if (file_order == 1)
	{
		if (access(file, F_OK) != -1)
		{
			if (access(file, R_OK) == -1)
				return (handle_error(file, 1), add_skip_flag(&data->cmds[i]),
					0);
		}
		else
			return (handle_error(file, 0), add_skip_flag(&data->cmds[i]), 0);
	}
	else if (file_order == 2)
	{
		if (stat(file, &sb) == 0 && S_ISDIR(sb.st_mode))
			return (handle_error(file, 3), add_skip_flag(&data->cmds[i]), 0);
		if (access(file, F_OK) != -1)
			if (access(file, W_OK) == -1)
				return (handle_error(file, 1), add_skip_flag(&data->cmds[i]),
					0);
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

int	check_out(t_data *data, int i)
{
	int		j;
	t_cmd	*cmd;
	int		flags;

	j = -1;
	cmd = &data->cmds[i];
	while (++j < cmd->out_redirs)
	{
		if (!check_permission(data, cmd->out[j], i, 2))
			return (0);
		flags = get_open_flags(cmd->append);
		if (data->fd2 >= 0)
		{
			close(data->fd2);
			data->fd2 = -1;
		}
		data->fd2 = open(cmd->out[j], flags, 0666);
		if (data->fd2 == -1)
			return (add_skip_flag(cmd),
				handle_error(cmd->out[j], 0), 0);
		if (j != cmd->out_redirs - 1)
			close(data->fd2);
	}
	return (1);
}

int	check_in(t_data *data, int i)
{
	int		j;
	t_cmd	*cmd;

	j = -1;
	cmd = &data->cmds[i];
	while (++j < cmd->in_redirs)
	{
		if (!check_permission(data, cmd->in[j], i, 1))
			return (0);
		if (j == cmd->in_redirs - 1)
		{
			if (data->fd1 >= 0)
			{
				close(data->fd1);
				data->fd1 = -1;
			}
			data->fd1 = open(cmd->in[j], O_RDONLY);
			if (data->fd1 == -1)
				return (add_skip_flag(cmd),
					handle_error(cmd->in[j], 0), 0);
		}
	}
	return (1);
}
