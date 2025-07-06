#include "minishell.h"

int	add_env(t_data *data, char *var, char *content)	//
{
	int		i;
	char	**tmp;
	char	*new;

	i = 0;
	if (!content)
		return (-1);
	tmp = ft_calloc(data->envp_size + 2, sizeof(char *));
	if (!tmp)
		return (-1);
	new = double_join(var, "=", content);
	if (!new)
		return (free(tmp), -1);
	while (data->envp && data->envp[i])
	{
		tmp[i] = data->envp[i];
		i++;
	}
	tmp[i] = new;
	free(data->envp);
	data->envp = tmp;
	data->envp_size++;
	return (0);
}

int	no_env(t_data *data)	//
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (-1);
	if (add_env(data, "PWD", pwd) != 0)
		return (free(pwd), -1);
	free(pwd);
	data->envp_size = arr_len(data->envp);
	return (0);
}

int	copy_envp(t_data *data, char **envp)	//
{
	int	i;

	i = 0;
	if (!*envp)
		return (no_env(data));
	while (envp[i])
		i++;
	data->envp = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!data->envp)
		return (-1);
	i = 0;
	while (envp[i])
	{
		data->envp[i] = ft_strdup(envp[i]);
		if (!data->envp[i])
			return (free_split(data->envp), -1);
		i++;
	}
	data->envp_size = arr_len(data->envp);
	return (0);
}
