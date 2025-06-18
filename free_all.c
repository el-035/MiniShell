/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <apchelni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 00:54:42 by apchelni          #+#    #+#             */
/*   Updated: 2025/04/18 17:48:36 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	free_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		// free(tmp->cmd);
		free(tmp);
	}
} */

void	free_str_arr(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
	str = NULL;
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = -1;
	if (!cmd)
		return ;
	if (cmd->args)
		free_str_arr(cmd->args);
	if (cmd->in)
	{
		free(cmd->in);
		cmd->in = NULL;
	}
	if (cmd->out)
	{
		free(cmd->out);
		cmd->out = NULL;
	}
	if (cmd->hd_content)
		free_str_arr(cmd->hd_content);
	if (cmd->limiter)
		free(cmd->limiter);
}

void	free_pipes(int ***pipes, int count)
{
	int	i;

	i = -1;
	while (++i < count - 1)
		free((*pipes)[i]);
	free(*pipes);
	*pipes = NULL;
}

static void	close_fds(t_data *data)
{
	if (data->fd1 >= 0)
	{
		close(data->fd1);
		data->fd1 = -1;
	}
	if (data->fd2 >= 0)
	{
		close(data->fd2);
		data->fd2 = -1;
	}
}

void	free_all(t_data *data)
{
	int	i;

	if (data->env_path != NULL)
	{
		free_str_arr(data->env_path);
		data->env_path = NULL;
	}
	if (data->pipes != NULL)
		free_pipes(&data->pipes, data->cmd_count);
	if (data->pid != NULL)
	{
		free(data->pid);
		data->pid = NULL;
	}
	if (data->cmds)
	{
		i = data->cmd_count;
		while (--i >= 0)
			free_cmd(&data->cmds[i]);
		free(data->cmds);
		data->cmds = NULL;
	}
	close_fds(data);
}

void	handle_error(char *str, int error_code)
{
	if (error_code == 0)
	{
		write(2, str, ft_strlen(str));
		write(2, ": No such file or directory\n", 28);
		return_exit_code(1);
	}
	else if (error_code == 1)
	{
		write(2, str, ft_strlen(str));
		write(2, ": Permission denied\n", 20);
	}
	else if (error_code == 2)
	{
		write(2, str, ft_strlen(str));
		write(2, ": command not found\n", 20);
	}
}
