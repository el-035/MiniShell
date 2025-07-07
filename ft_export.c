#include "minishell.h"

int	ft_is_valid(char *cmd) //
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

int	find_var(char **envp, char *str) //
{
	char	*var;
	int		len;
	int		i;

	i = 0;
	var = ft_strjoin(str, "=");
	if (!var)
		return (fail_mall(), -2);
	len = ft_strlen(var);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0)
			return (free(var), i);
		i++;
	}
	free(var);
	return (-1);
}

int	append(char *var, char *cmd, t_data *data, int index) //
{
	char	*new;
	char	*old;
	char	*app;

	new = get_content(cmd);
	if (!new)
		return (fail_mall(), -1);
	old = get_content(data->envp[index]);
	if (!old)
		return (free(new), fail_mall(), -1);
	app = ft_strjoin(old, new);
	free(new);
	free(old);
	if (!app)
		return (fail_mall(), -1);
	new =double_join(var, "=", app);
	if (!new)
		return (free(app), fail_mall(), -1);
	free(data->envp[index]);
	data->envp[index] = new;
	return (free(app), 0);
}

int	replace(char *var, char *cmd, t_data *data, int index) //
{
	char	*content;
	char	*new;

	content =get_content(cmd);
	if (!content)
		return (fail_mall(), -1);
	new = double_join(var, "=", content);
	if (!new)
		return (free(content), fail_mall(), -1);
	free(data->envp[index]);
	data->envp[index] = new;
	return (free(content), 0);
}

int	export_helper(char *args, t_data *data, char *var) //
{
	char	*content;
	int		index;

	content = get_content(args);
	if (!content)
		return (-1);
	index = find_var(data->envp, var);
	if (index == -2)
		return (free(content), -1);
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
	else
	{
		if (replace(var, args, data, index) == -1)
			return (free(content), -1);
	}
	return (free(content), 0);
}

void	ft_export(t_data *data, t_cmd *cmd) //
{
	int		i;
	char	*var;

	i = 0;
	if (!cmd->args[1])
		print_export(data->envp);
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
