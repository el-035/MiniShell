/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <apchelni@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 00:54:42 by apchelni          #+#    #+#             */
/*   Updated: 2025/04/18 17:48:36 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static char	*check_path(t_data *data, char *cmd)
{
	char	*path;
	char	*tmp;
	int		i;

	i = -1;
	tmp = NULL;
	if (!cmd || *cmd == '\0')
		return (handle_error(cmd, 2), NULL);
	if (data->env_path && *data->env_path && cmd && *cmd)
		while (data->env_path[++i] != NULL)
		{
			if (tmp != NULL)
				free(tmp);
			path = ft_strjoin(data->env_path[i], "/");
			if (!path)
				return (fail_mall(), NULL);
			tmp = ft_strjoin(path, cmd);
			free(path);
			if (!tmp)
				return (fail_mall(), NULL);
			if (access(tmp, X_OK) == 0)
				return (tmp);
		}
	else
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
			else
				return (handle_error(cmd, 0), NULL);
	return (free(tmp), handle_error(cmd, 2), NULL);
}*/

static char *create_path(char *cmd, char *env_path)
{
	char	*path;
	char	*tmp;
	
	path = ft_strjoin(env_path, "/");
	if (!path)
		return (NULL);
	tmp = ft_strjoin(path, cmd);
	free(path);
	if (!tmp)
		return (NULL);
	return (tmp);
}

static char	*check_path(t_data *data, char *cmd)
{
	char	*tmp;
	int		i;

	i = -1;
	if (!cmd || *cmd == '\0')
		return (handle_error(cmd, 2), NULL);
	if (data->env_path && *data->env_path && cmd && *cmd)
		while (data->env_path[++i] != NULL)
		{
			tmp = create_path(cmd, data->env_path[i]);
			if (!tmp)
				return (fail_mall(), NULL);
			if (access(tmp, X_OK) == 0)
				return (tmp);
		}				
	else if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	else
		return (handle_error(cmd, 0), NULL);
	return (free(tmp), handle_error(cmd, 2), NULL);
}

static int	execute_cmd(t_data *data, char **args, char **envp)
{
	char	*path;

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
			return (return_exit_code(1), 0);
	}
	if (execve(path, args, envp) == -1)
	{
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
	if (index < data->cmd_count - 1)
		dup2(data->pipes[index][1], STDOUT_FILENO);
	i = -1;
	while (++i < data->cmd_count - 1)
	{
		if (data->pipes)
			(close(data->pipes[i][0]), close(data->pipes[i][1]));
	}
	if (cmd->in == NULL && data->fd1 != STDIN_FILENO && data->fd1 != -1)
		close(data->fd1);
	if (cmd->out == NULL && data->fd2 != STDOUT_FILENO && data->fd2 != -1)
		close(data->fd2);
}

int	exec_child(t_data *data, int index, char **envp)
{
	t_cmd				*cmd;
	struct sigaction	sig;

	sig.sa_handler = &child_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
	cmd = &data->cmds[index];
	set_child_fds(data, cmd, index);
	if (cmd->is_hd == 1)
		exec_hd(data, cmd, index);
	if (cmd->is_builtin)
		(exec_builtin_child(cmd, data), free_split(data->envp), free_all(data),
			exit(EXIT_SUCCESS));
	if (!cmd->args || !cmd->args[0])
	{
		if (cmd->is_hd == 1)
			(free_split(data->envp), free_all(data), exit(EXIT_SUCCESS));
		else
			(free_split(data->envp), free_all(data), exit(EXIT_FAILURE));
	}
	if (!execute_cmd(data, cmd->args, envp))
		(free_split(data->envp), free_all(data), exit(127));
	(free_split(data->envp), free_all(data), exit(EXIT_SUCCESS));
}
