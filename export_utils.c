#include "minishell.h"

char	*get_var(char *str)
{
	int		i;
	char	*var;

	i = 0;
	if (!ft_strchr(str, '='))
		return (ft_strdup(str));
	while (str[i] != '=' /*  && str[i] != '+' */)
		i++;
	var = ft_calloc(i + 1, sizeof(char));
	if (!var)
		return (NULL); // erroere
	i = 0;
	while (str[i] != '=' /*  && str[i] != '+' */)
	{
		var[i] = str[i];
		i++;
	}
	return (var);
}

char	*get_content(char *str)
{
	int		i;
	int		len;
	char	*conetnt;

	if (!ft_strchr(str, '='))
		return (NULL);
	len = ft_strlen(ft_strchr(str, '=') + 1);
	conetnt = ft_calloc(len + 1, sizeof(char));
	if (!conetnt)
		return (NULL); // erroere
	str = ft_strchr(str, '=') + 1;
	i = -1;
	while (str[++i])
		conetnt[i] = str[i];
	return (conetnt);
}

char	**copy(char **envp)
{
	char	**cpy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cpy = ft_calloc(arr_len(envp), sizeof(char *));
	if (!cpy)
		return (NULL); // euwei
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "_=", 2) == 0)
			i++;
		cpy[j++] = ft_strdup(envp[i++]); // protect
	}
	return (cpy);
}

void	sort(char **cpy)
{
	int		flag;
	char	*tmp;
	int		i;

	flag = 1;
	i = 0;
	while (flag != 0)
	{
		flag = 0;
		i = 0;
		while (cpy[i + 1])
		{
			if (ft_strncmp(cpy[i], cpy[i + 1], ft_strlen(cpy[i])) > 0)
			{
				tmp = cpy[i];
				cpy[i] = cpy[i + 1];
				cpy[i + 1] = tmp;
				flag = 1;
			}
			i++;
		}
	}
}

int	print_export(char **envp)
{
	char	**cpy;
	int		i;
	char	*var;
	char	*content;

	i = 0;
	cpy = copy(envp);
	if (!cpy)
		return (1); // ghhuijk
	sort(cpy);
	while (cpy[i])
	{
		var = get_var(cpy[i]);         // protect
		content = get_content(cpy[i]); // protect
		printf("declare -x %s=\"%s\"\n", var, content);
		free(var);
		free(content);
		i++;
	}
	free_split(cpy);
	return (0);
}
