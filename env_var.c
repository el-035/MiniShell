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
	char	*temp;
	char	*joint;
	//int		index_flag;

/* 	index_flag = 0;
	if (find_index(-1) != 0 && (ft_strlen(start) + 1) != find_index(-1)
		&& find_index(-1) != -1)
		index_flag = 1; */
	joint = ft_strjoin(start, var);
	if (!joint)
		return (free(start), free(var), free(end), 1);
	free(start);
	free(var);
	temp = ft_strjoin(joint, end);
	if (!temp)
		return (free(end), free(joint), 1);
	free(joint);
	/* if (index_flag == 1)
		find_index(exp_helper(temp)); */
	joint = temp;
	free(end);
	free(*content);
	*content = ft_strdup(joint);
	free(joint);
	if (!*content)
		return (1);
	return (0);
}

void	save_var_index(int *dq_count, int index)
{
	int i;

	i = 0;
	while (dq_count[i] != -1)
		i++;
	dq_count[i] = index;
}

int	expand_var(char **content, char **envp, int **dq_count)
{
	char	*start;
	char	*var;
	char	*end;

	if (stop(*content) == 0)
		return (0);
	start = save_start(*content); // HERE malloc faisl ???+
	if (!start)
		return (fail_mall(), 1);
	/* if (dq_count != NULL)
		save_var_index((*dq_count), ft_strlen(start)); */
	var = save_var(&(*content)[start_len(*content)]);
	if (!var)
		return (free(start), 1);
	end = save_rest(search_var(*content, var), var);
	if (!end)
		return (free(start), free(var), fail_mall(), 1);
	var = extract_var(envp, var);
	if (!var)
		return (free(start), free(end), fail_mall(), 1);
	if (join_all(content, start, end, var) == 1)
		return (fail_mall(), 1);
	if (ft_strchr(*content, '$') != 0)
		expand_var(content, envp, dq_count);
	return (0);
}

int	exp_helper(char *content)
{
	int	i;
	int count;

	i = 0;
	count = 0;
	while (content[i])
	{
		if (content[i] == '$' && check_quotes(content, i) == 0)
			count++;
		i++;
	}
	if (count == 0)	
		return (-1);
	return (count);
}

int init_dq(t_input *cur)
{
	int len;
	int i;

	i = 0;
	len = exp_helper(cur->content);
	cur->dq_var = (int *) ft_calloc(len + 1, sizeof(int));
	if (!cur->dq_var)
		return (fail_mall(), 1);
	while(i <= len)
		cur->dq_var[i++] = -1;
	return 0;
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
			/* if (exp_helper(cur->content) != -1)
				if (init_dq(cur) != 0)
					return 1; */

			if (expand_var(&(cur->content), data->envp, &(cur->dq_var)) != 0)
				return (1);
			//printf("Expanded var at index: %d\n", (*dq_count)[i]);
		}
		if ((!cur->prev || cur->prev->type != HERE_DOC)
			&& ft_strnstr(cur->content, "$?", ft_strlen(cur->content)))
		{
			if (expand_exit(&cur, data) != 0)
				return (1);
		}
		if ((ft_strchr(cur->content, '\'') || ft_strchr(cur->content, '"')))
		{
			if (remove_useless_quotes(cur) != 0)
				return (1);
		}
		cur = cur->next;
		if (cur == first)
			break ;
	}
	return (0);
}
