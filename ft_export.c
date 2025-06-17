#include "minishell.h"

int ft_is_valid(char *str)
{
	int i;

	i = 0;
	if(!ft_isalpha(str[i]) && str[i] != '_')
		return (1);	
	while (str[i])
	{
		if(!ft_isalnum(str[i]) && str[i] != '_')
			return (1);	
		i++;
	}
	return (0);
}

char	*get_var(char *str)
{
	int i;
	char *var;

	i = 0;
	if (!ft_strchr(str, '='))
		return (ft_strdup(str));
	while (str[i] != '=' && str[i] != '+')
		i++;
	var = ft_calloc(i + 1, sizeof(char));
	if (!var)
		return (NULL); //erroere
	i = 0;
	while (str[i] != '=' && str[i] != '+')
	{
		var[i] = str[i];
		i++;
	}
	return (var);
}

char	*get_content(char *str)
{
	int i;
	int len;
	char *conetnt;

	if (!ft_strchr(str, '='))
		return (NULL);
	len = ft_strlen(ft_strchr(str, '=') + 1);
	conetnt = ft_calloc(len + 1, sizeof(char));
	if (!conetnt)
		return (NULL); //erroere
	str = ft_strchr(str, '=') + 1;
	i = -1;
	while (str[++i])
		conetnt[i] = str[i];
	return (conetnt);
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
	if (ft_is_valid(var) != 0)
	{
		write(2, "bash: export: `", 15);
		write(2, cmd->args[i], ft_strlen(cmd->args[i]));
		write(2, "': not a valid identifier\n", 27);
		return_exit_code(1);
	}
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
		printf("print all var declare x ascii order no_...\n");
	while (cmd->args[++i])
	{
		var = get_var(cmd->args[i]);	//protect
		export_helper(data, cmd, i, var);
		free(var);
	}
}
//if only export print all exported var with declare x in ascii order, not _=/usr/bin/env
//check syntax
// (accept more variables in one)
//if var already exits update
//else add
