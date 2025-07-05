#include "minishell.h"

char	*save_start(char *content)
{
	int		i;
	int		len;
	char	*start;

	i = 0;
	len = start_len(content);
	if (len == 0)
		return (ft_strdup(""));
	start = (char *)ft_calloc((len + 1), sizeof(char));
	if (!start)
		return (NULL);
	while (i < len)
	{
		start[i] = content[i];
		i++;
	}
	return (start);
}

char	*save_rest(char *content, char *var)
{
	int		i;
	int		len;
	char	*rest;

	len = ft_strlen(var);
	if (!content[len] || !content || !*content)
		return (ft_strdup(""));
	i = len;
	while (content[len])
		len++;
	len = len - i;
	rest = (char *)ft_calloc((len + 1), sizeof(char));
	if (!rest)
		return (NULL); //
	len = 0;
	while (content[i])
		rest[len++] = content[i++];
	return (rest);
}

int	join_all(char **content, char *start, char *end, char *var)
{
	free(*content);
	*content = double_join(start, var, end);
	free(start);
	free(var);
	free(end);
	if (!*content)
		return (1);
	return (0);
}

int	expand_var(char **content, char **envp)
{
	char	*start;
	char	*var;
	char	*end;

	if (stop(*content) == 0)
		return (0);
	start = save_start(*content); // HERE malloc faisl ???+
	if (!start)
		return (fail_mall(), 1);
	var = save_var(&(*content)[start_len(*content)]);
	if (!var)
		return (free(start), 1);
	end = save_rest(search_var(*content, var) + 1, var);
	if (!end)
		return (free(start), free(var), fail_mall(), 1);
	var = extract_var(envp, var);
	if (!var)
		return (free(start), free(end), fail_mall(), 1);
	if (join_all(content, start, end, var) == 1)
		return (fail_mall(), 1);
	if (ft_strchr(*content, '$') != 0)
		expand_var(content, envp);
	return (0);
}

int	find_ev(t_input *first, t_data *data)
{
	t_input	*cur;

	cur = first;
	while (cur)
	{
		if ((!cur->prev || cur->prev->type != HERE_DOC)
			&& stop(cur->content) != 0)
		{
			if (exp_tokenise(cur, data->envp) == -1) // protect
				return (1);
		}
		if ((!cur->prev || cur->prev->type != HERE_DOC) && cur->content
			&& ft_strnstr(cur->content, "$?", ft_strlen(cur->content)))
		{
			if (expand_exit(&cur, data) != 0)
				return (1);
		}
		cur = cur->next;
		if (cur == first)
			break ;
	}
	return (0);
}
