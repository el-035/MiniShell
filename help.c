#include "minishell.h"

void	actual_print(char *var, char *content)
{
	write(1, "declare -x ", 11);
	ft_putstr_fd(var, 1);
	if (content != NULL)
	{
		write(1, "=\"", 2);
		ft_putstr_fd(content, 1);
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
}


int	add_empty_env(t_data *data, char *var)
{
	int		i;
	char	**tmp;
	char	*new;

	i = 0;
	tmp = ft_calloc(data->envp_size + 2, sizeof(char *));
	if (!tmp)
		return (-1);
	new = ft_strdup(var);
	if (!new)
		return (free(tmp), fail_mall(), -1);
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


int	find_exp_var(char **envp, char *str)
{
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(str);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, len) == 0)
		{
			if (envp[i][len] == '=' || envp[i][len] == '\0')
				return (i);
		}
		i++;
	}
	return (-1);
}