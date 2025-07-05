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

int	find_var(char **envp, char *str)
{
	char	*var;
	int		i;

	i = 0;
	var = ft_strjoin(str, "=");
	if (!var)
		return (fail_mall(), -2);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
			return (free(var), i);
		i++;
	}
	free(var);
	return (-1);
}
/* 
char	*append_replace(char *arg, char *content, char *prev)
{
	char	*tmp;
	char	*app;

	app = NULL;
	tmp = ft_strchr(arg, '+');
	if (!tmp)
		return (free(prev), ft_strdup(content));
	tmp++;
	if (tmp[0] == '=')
	{
		app = ft_strjoin(prev, content);
		if (!app)
			return (fail_mall(), free(prev), NULL);
		free(prev);
	}
	return (app);
} */

/*  void	export_helper(t_data *data, t_cmd *cmd, int i, char *var)
{
	char	*content;
	char	*tmp;
	int		j;
	char	*alloc;

	content = get_content(cmd->args[i]);
	if (!content)
		return ;
	if (find_var(data->envp, var) != -1)
	{
		j = find_var(data->envp, var);
		tmp = append_replace(cmd->args[i], content, get_content(data->envp[j]));
		if (!tmp)
			return (free(content));
		alloc = double_join(var, "=", tmp);
		if (!alloc)
			return (free(content), free(tmp));
		free(data->envp[j]);
		data->envp[j] = alloc;
		free(tmp);
	}
	else if (find_var(data->envp, var) == -1)
		add_env(data, var, content);
			// not printinf error message but otherwise too many lines
	return (free(content));
}  */

int append(char *var, char *cmd, t_data *data)
{
	char *new;
	char *old;
	char *app;
	int	j;

	j = find_var(data->envp, var);
	new = get_content(cmd);
	if (!new)
		return (fail_mall(), -1);
	old = get_content(data->envp[j]);
	if (!old)
		return (free(new), fail_mall(), -1);
	app = ft_strjoin(old, new);
	free(new); free(old);
	if (!app)
		return (fail_mall(), -1);
	new = double_join(var, "=", app);
	if (!new)
		return (free(app), fail_mall(), -1);
	free(data->envp[j]);
	data->envp[j] = new;
	return (free(app), 0);
}

int replace(char *var, char *cmd, t_data *data)
{
	char *content;
	int j;
	char *new;

	j = find_var(data->envp, var);
	content = get_content(cmd);
	if (!content)
		return (fail_mall(), -1);
	new = double_join(var, "=", content);
	if (!new)
		return (free(content), fail_mall(), -1);
	free(data->envp[j]);
	data->envp[j] = new;
	return (free(content), 0);
}

int export_helper(char *args, t_data *data, char *var)
{
	/* char *tmp; */

	/* tmp = ft_strchr(args, '='); */
	if (find_var(data->envp, var) == -1)
	{
		if (add_env(data, var, get_content(args)) == -1)
			return (fail_mall(), -1); 
	}
	else if (args[ft_strlen(var)] == '+' )
	{
		if (append(var, args, data) == -1)
			return (free(var), -1);
	}
	else
	{
		if (replace(var, args, data) == -1)
			return (free(var), -1);
	}
	return (0);
}

void	ft_export(t_data *data, t_cmd *cmd)
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
			if (export_helper(cmd->args[i], data, var) == -1)	//protect
				return (free(var));
		}
		free(var);
	}
}
