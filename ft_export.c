#include "minishell.h"

char *double_join(char *s1, char *s2, char *s3)	//those are not allocated
{
	char *tmp;
	char *final;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (write(2, "Allocation failed\n", 18), NULL);
	final = ft_strjoin(tmp, s3);
	if (!final)
		return (write(2, "Allocation failed\n", 18), free(tmp), NULL);
	return (free(tmp), final);
}

int	add_env(t_data *data, char *var, char *content)
{
	int len;
	int i;
	char **tmp;

	i = 0;
	len = arr_len(data->envp);
	tmp = ft_calloc(len + 2, sizeof(char *));
	if (!tmp)
		return (write(2, "Allocation failed\n", 18), 1);
	while(data->envp && data->envp[i])
	{
		tmp[i] =  ft_strdup(data->envp[i]);
		if (!tmp[i])
			return (write(2, "Allocation failed\n", 18), 1);	//freesplit
		i++;
	}
	tmp[i] = double_join(var, "=", content);
	free_split(data->envp);
	data->envp = tmp;
	return 0;
}

int ft_is_valid(char *str)
{
	int i;

	i = 0;
	while (str[i] != '=')
	{
		if(!ft_isalpha(str[i]) || str[i] != '_')
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
	while (str[i] != '=')
		i++;
	var = ft_calloc(i + 1, sizeof(char));
	if (!var)
		return (NULL); //erroere
	i = 0;
	while (str[i] != '=')
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

	len = ft_strlen(ft_strchr(str, '='));
	conetnt = ft_calloc(len + 1, sizeof(char));
	if (!conetnt)
		return (NULL); //erroere
	i = 0;
	while (str[i])
		conetnt[i++] = str[len++];
	return (conetnt);
}


int	ft_export(t_data *data, t_cmd *cmd)
{
	int i;
	char *var;
	char *content;

	i = 1;
	if (!cmd->args[1])
		printf("print all var declare x ascii order no_...\n");
	while (cmd->args[i])
	{
		var = get_var(cmd->args[i]);
		
		if (ft_is_valid(cmd->args[i]) != 0)
		{
			write(2, "minishell: export: `", 21);
			write(2, cmd->args[i], ft_strlen(cmd->args[i]));
			write(2, "' : not a valid identifier\n", 28);
		}
		//else if ()
		//if it exists --> update
		else
			add_env(data, )
			//add_env
	}
}
//if only export print all exported var with declare x in ascii order, not _=/usr/bin/env
//check syntax
// (accept more variables in one)
//if var already exits update 
//else add
