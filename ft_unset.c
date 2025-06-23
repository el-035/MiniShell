#include "minishell.h"

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

int	var_count(char **envp, char **args)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	if (!envp || !*envp)
		return (-1);
	while (envp[i])
	{
		j = 1;
		while (args[j])
		{
			if (ft_strncmp(envp[i], args[j], ft_strlen(args[j])) == 0
				&& envp[i][ft_strlen(args[j])] == '=')
			{
				count++;
				break ;
			}
			j++;
		}
		i++;
	}
	return (count);
}

int	copy_var(char *envp, char **var)
{
	int	i;

	i = 1;
	while (var[i])
	{
		if (ft_strncmp(envp, var[i], ft_strlen(var[i])) == 0
			&& (envp[ft_strlen(var[i])] == '='))
			return (0);
		i++;
	}
	return (1);
}

int	ft_unset(t_data *data, t_cmd *cmd)
{
	int		i;
	int		j;
	char	**tmp;

	if (!cmd->args[1])
		return (0);
	i = var_count(data->envp, cmd->args);
	if (i == 0)
		return (0);
	tmp = ft_calloc((arr_len(data->envp) - i) + 1, sizeof(char *));
	if (!tmp)
		return (fail_mall(), -1);
	i = 0;
	j = 0;
	while (data->envp[i])
	{
		if (copy_var(data->envp[i], cmd->args) == 1)
		{
			tmp[j++] = ft_strdup(data->envp[i]);
			if (!tmp[j - 1])
				return (free_split(tmp), fail_mall(), -1);
		}
		i++;
	}
	return (free_split(data->envp), data->envp = tmp, 0);
}
