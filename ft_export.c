/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <efittant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:29:53 by efittant          #+#    #+#             */
/*   Updated: 2025/07/11 22:05:33 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_valid(char *cmd)
{
	int	i;

	i = 0;
	if (!ft_isalpha(cmd[i]) && cmd[i] != '_')
		return (1);
	i++;
	while (cmd[i] && cmd[i] != '=' && cmd[i] != '+')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (1);
		i++;
	}
	if (!cmd[i])
		return (0);
	if (cmd[i] == '+')
	{
		if (!cmd[i + 1] || cmd[i + 1] != '=')
			return (1);
		i++;
	}
	if (cmd[i] != '=')
		return (1);
	return (0);
}

int	append(char *var, char *cmd, t_data *data, int index)
{
	char	*new;
	char	*old;
	char	*app;

	new = get_content(cmd);
	if (!new)
		return (fail_mall(), -1);
	if (ft_strchr(data->envp[index], '=') != NULL)
		old = get_content(data->envp[index]);
	else
		old = ft_strdup("");
	if (!old)
		return (free(new), fail_mall(), -1);
	app = ft_strjoin(old, new);
	free(new);
	free(old);
	if (!app)
		return (fail_mall(), -1);
	new = double_join(var, "=", app);
	if (!new)
		return (free(app), fail_mall(), -1);
	free(data->envp[index]);
	data->envp[index] = new;
	return (free(app), 0);
}

int	replace(char *var, char *cmd, t_data *data, int index)
{
	char	*content;
	char	*new;

	content = get_content(cmd);
	if (!content)
		return (fail_mall(), -1);
	new = double_join(var, "=", content);
	if (!new)
		return (free(content), fail_mall(), -1);
	free(data->envp[index]);
	data->envp[index] = new;
	return (free(content), 0);
}

int	export_helper(char *args, t_data *data, char *var)
{
	char	*content;
	int		index;

	index = find_exp_var(data->envp, var);
	content = NULL;
	if (!ft_strchr(args, '='))
		return (add_empty_env(data, var, index));
	content = get_content(args);
	if (!content)
		return (-1);
	if (index == -1)
	{
		if (add_env(data, var, content) == -1)
			return (free(content), fail_mall(), -1);
	}
	else if (args[ft_strlen(var)] == '+')
	{
		if (append(var, args, data, index) == -1)
			return (free(content), -1);
	}
	else if (replace(var, args, data, index) == -1)
		return (free(content), -1);
	return (free(content), 0);
}

void	ft_export(t_data *data, t_cmd *cmd)
{
	int		i;
	char	*var;

	i = 0;
	if (!cmd->args[1])
		print_export(data->envp, data, 0);
	while (cmd->args[++i])
	{
		var = get_var(cmd->args[i]);
		if (!var)
			return (fail_mall());
		if (ft_is_valid(cmd->args[i]) != 0)
		{
			write(2, "bash: export: `", 15);
			write(2, cmd->args[i], ft_strlen(cmd->args[i]));
			write(2, "': not a valid identifier\n", 26);
			return_exit_code(1);
		}
		else
		{
			if (export_helper(cmd->args[i], data, var) == -1)
				return (free(var));
		}
		free(var);
	}
}
