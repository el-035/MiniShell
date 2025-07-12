/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <apchelni@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 00:54:42 by apchelni          #+#    #+#             */
/*   Updated: 2025/04/18 17:48:36 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin_child(t_cmd *cmd, t_data *data)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		ft_env(data->envp);
	else
		return ;
}

static int	is_valid_numeric(const char *str)
{
	int	i = 0;

	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (str[i] == '\0');
}

int	exec_builtin_parent(t_cmd *cmd, t_data *data)
{
	if (ft_strcmp(cmd->args[0], "export") == 0 && data->cmd_count == 1)
		ft_export(data, cmd);
	else if (ft_strcmp(cmd->args[0], "unset") == 0  && data->cmd_count == 1)
		ft_unset(data, cmd);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
	{
		if (data->cmd_count == 1)
			ft_cd(data, cmd);
		else if (access(cmd->args[1], F_OK) == -1)
			(write(2, "cd: ", 4), handle_error(cmd->args[1], 0));
		else if (access(cmd->args[1], X_OK) == -1)
			(write(2, "cd: ", 4), handle_error(cmd->args[1], 1));
	}
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
	{
		if (cmd->args[1] && !is_valid_numeric(cmd->args[1]))
			ft_exit(data, cmd);
		else if (cmd->args[1] && cmd->args[2])
			(write(2, "exit: too many arguments\n", 25), return_exit_code(1));
	//UPDATE ERROR CODE IF THE LAST
			else if (data->cmd_count > 1)
			{
				data->ec_update_flag = 1;
			}
		else
			ft_exit(data, cmd);
	}
	else
		return (1);
	return (0);
}
