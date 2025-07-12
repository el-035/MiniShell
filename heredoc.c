/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <efittant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 00:54:42 by apchelni          #+#    #+#             */
/*   Updated: 2025/07/12 23:03:50 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_heredoc(t_cmd *cmd, t_input **cur, char **envp)
{
	if (!(*cur)->next)
		return (0);
	if (cmd->limiter)
		free(cmd->limiter);
	cmd->limiter = ft_strdup((*cur)->next->content);
	if (!cmd->limiter)
		return (fail_mall(), 0);
	if (!create_heredoc(cmd, envp))
		return (0);
	cmd->is_hd = 1;
	*cur = (*cur)->next;
	return (1);
}

static int	create_hd_filename(char *name, int size, int index)
{
	int		hd_id;
	char	*id_str;
	int		fd;

	hd_id = 0;
	while (hd_id < 1000)
	{
		id_str = ft_itoa(index + hd_id);
		if (!id_str)
			return (0);
		if (ft_strlen("/tmp/heredoc_") + ft_strlen(id_str) + 1 > size)
			return (free(id_str), -1);
		(ft_strlcpy(name, "/tmp/heredoc_", size), ft_strlcat(name, id_str,
				size), free(id_str));
		fd = open(name, O_CREAT | O_EXCL | O_RDWR, 0600);
		if (fd != -1)
			return (fd);
		hd_id++;
	}
	return (-1);
}

int	set_heredoc_fds(t_cmd *cmd, int index)
{
	char	tmp_name[64];
	int		fd;
	int		i;

	fd = create_hd_filename(tmp_name, sizeof(tmp_name), index);
	if (fd < 0)
		return (perror("Open heredoc file"), 0);
	if (cmd->hd_in)
	{
		unlink(cmd->hd_in);
		free(cmd->hd_in);
		cmd->hd_in = NULL;
	}
	cmd->hd_in = ft_strdup(tmp_name);
	if (!cmd->hd_in)
		return (close(fd), fail_mall(), 0);
	i = -1;
	while (cmd->hd_content && cmd->hd_content[++i])
	{
		write(fd, cmd->hd_content[i], ft_strlen(cmd->hd_content[i]));
		write(fd, "\n", 1);
	}
	close(fd);
	return (return_exit_code(0), 1);
}

void	exec_hd(t_data *data, t_cmd *cmd, int index)
{
	int	fd;

	if (cmd->hd_content)
	{
		if (!set_heredoc_fds(cmd, index))
			(free_split(data->envp), free_all(data), rl_clear_history(), exit(EXIT_FAILURE));
		fd = open(cmd->hd_in, O_RDONLY);
		if (fd < 0)
			(perror("Opening heredoc tmp file"), free_split(data->envp),
				free_all(data), rl_clear_history(), exit(EXIT_FAILURE));
		(dup2(fd, STDIN_FILENO), close(fd), unlink(cmd->hd_in));
	}
	else
		(close_child(data), exit(EXIT_SUCCESS));
}
