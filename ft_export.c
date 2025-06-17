#include "minishell.h"

int ft_is_valid(char *str)
{
	int i;

	i = 0;
	if(!ft_isalpha(str[i]) && str[i] != '_')
		return (1);
	i++;
	while (str[i])
	{
		if(!ft_isalnum(str[i]) && str[i] != '_')
			return (1);	
		i++;
	}
	return (0);
}

int find_var(char **envp, char *str)
{
	char *var;
	int i;

	i = 0;
	var = ft_strjoin(str, "=");		//protect
	while(envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
			return (free(var), i);
		i++;
	}
	free(var);
	return (-1);
}

char	*append_replace(char *arg, char *var, char *content, char *prev)
{
	char *tmp;
	char *app;

	tmp = ft_strchr(arg, '+');
	if (!tmp)
		return (ft_strdup(content));
	tmp++;
	if (tmp[0] == '=')
	{
		app = ft_strjoin(prev, content);
			//protect this sht
		free(prev);

	}
	return (app);
}

void	export_helper(t_data *data, t_cmd *cmd, int i, char *var)
{
	char *content;
	char *tmp;
	int j;

	content = get_content(cmd->args[i]);
	if (!content)
		return ;
	else if (find_var(data->envp, var) != -1)
	{
		j = find_var(data->envp, var);
		tmp = append_replace(cmd->args[i], var, content, get_content(data->envp[j]));
		free(data->envp[j]);
		data->envp[j] = double_join(var, "=", tmp);
		free(tmp);
	}
	else
		add_env(data, var, content);
	free(content);
}

void	ft_export(t_data *data, t_cmd *cmd)
{
	int i;
	char *var;

	i = 0;
	if (!cmd->args[1])
		print_export(data->envp);	
	//printf("print all var declare x ascii order no_...\n");
	while (cmd->args[++i])
	{
		var = get_var(cmd->args[i]);	//protect

		if (ft_is_valid(var) != 0)
		{
			write(2, "bash: export: `", 15);
			write(2, cmd->args[i], ft_strlen(cmd->args[i]));
			write(2, "': not a valid identifier\n", 26);
			return_exit_code(1);
		}
		else
		{
			export_helper(data, cmd, i, var);
			free(var);
		}
	}
}
