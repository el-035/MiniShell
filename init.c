#include "minishell.h"

void	init_input(t_input *first)
{
	first->content = NULL;
	first->type = UNKNOWN;
	first->position = -1;
	first->next = NULL;
	first->prev = NULL;
	first->is_builtin = -1;
	first->exp = -1;
}

int	save_input(char *line, t_input **first)
{
	t_input	*cur;
	char	**split;
	int		pos;

	pos = 0;
	split = mini_split(line);
	if (!split)
		return (0);
	*first = make_new_node(split[pos], pos);
	if (!*first)
		return (free_split(split), fail_mall(), 0);
	cur = *first;
	if (!split[1])
	{
		(*first)->next = (*first);
		(*first)->prev = (*first);
	}
	while (split[++pos])
	{
		cur = add_new(split[pos], pos, cur);
		if (!cur)
			return (free_split(split), free_list(*first), fail_mall(), 0);
	}
	if (pos > 1)
	{
		cur->next = *first;
		(*first)->prev = cur;
	}
	return (free_split(split), 1);
}

char	*double_join(char *s1, char *s2, char *s3) // those are not allocated
{
	char	*tmp;
	char	*final;

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
	int		len;
	int		i;
	char	**tmp;

	i = 0;
	len = arr_len(data->envp);
	tmp = ft_calloc(len + 2, sizeof(char *));
	if (!tmp)
		return (-1);
	while (data->envp && data->envp[i])
	{
		tmp[i] = ft_strdup(data->envp[i]);
		if (!tmp[i])
			return (free_split(data->envp), free_split(tmp), -1);
		i++;
	}
	tmp[i] = double_join(var, "=", content);
	if (!tmp[i])
		return (free_split(data->envp), free_split(tmp), -1);
	free_split(data->envp);
	data->envp = tmp;
	return (0);
}

int	no_env(t_data *data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (-1);
	if (add_env(data, "PWD", pwd) != 0)
		return (free(pwd), -1); // freeeee
	free(pwd);
	if (add_env(data, "SHLVL", "0") != 0)
		return (free_split(data->envp), -1); // freeeee
	if (add_env(data, "_", "/usr/bin/env") != 0)
		return (free_split(data->envp), -1); // freeeee
	return (0);
}

int	copy_envp(t_data *data, char **envp)
{
	int i;

	i = 0;
	if (!*envp) // IDK HOW TO VALGRIND THIS
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
	return (0);
}
