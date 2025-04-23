#include"minishell.h"

int	check_quotes(char *content, int len)
{
	int	quote;
	int i;

	i = 0;
	quote = 0;
	while (content[i] && i <= len)
	{
		if (content[i] == '\'' && quote == 0)
			quote = 1;
		else if (content[i] == '\'' && quote == 1)
			quote = 0;
		else if (content[i] == '"' && quote == 0)
			quote = 2;
		else if (content[i] == '"' && quote == 2)
			quote = 0;
		i++;
	}
	if (quote == 1)
		return 1;
	if (quote == 2)
		return 2;
	return 0;
}

int	start_len(char *content)
{
	int i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '$')
		{
			if (content[i + 1] && (content[i + 1] == '$' /* || content[i + 1] == '?' */))
				i += 2;
			else if (content[i + 1] && !(ft_isalpha(content[i + 1]) || content[i + 1] == '_'))
				i++;
			else if (check_quotes(content, i) == 1)
				i++;
			else
				return (i);	//variable to be expanded found
		}
		else
			i++;
	}
	return i; //nothing left to do
}
int	stop(char *content)
{
	int i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '$')
		{
			if (content[i + 1] && (content[i + 1] == '$' /* || content[i + 1] == '?' */))
				i += 2;
			else if (content[i + 1] && !(ft_isalpha(content[i + 1]) || content[i + 1] == '_'))
				i++;
			else if (check_quotes(content, i) == 1)
				i++;
			else
				return (1);	//variable to be expanded found
		}
		else
			i++;
	}
	return 0; //nothing left to do
}

char *save_start(char *content)
{
	int i;
	int len;
	char *start;

	i = 0;
	len = start_len(content);
	if (len == 0)
		return (ft_strdup(""));
	start = (char *) ft_calloc((len + 1), sizeof(char));
	if (!start)
		return (printf("Allocation failed\n"), NULL); //
	while(i < len)
	{
		start[i] = content[i];
		i++;
	}
	return (start);
}

char	*save_var(char *content)
{
	int i;
	int len;
	char *var;

	i = -1;
	len = 0;

	if (!content || !*content)
		return (NULL);
	if (content[1])
		content++;
	while (content[len])
	{
		if (ft_isalpha(content[len]) || content[len] == '_')
			len++;
		else
			break;
	}
	var = (char *) ft_calloc((len + 1), sizeof(char));
	if (!var)
		return (printf("Allocation failed\n"), NULL); //
	while (++i < len)
		var[i] = content[i];
	return (var);
}

char	*save_rest(char *content, char *var)
{
	int i;
	int len;
	char *rest;

	len = ft_strlen(var);

	if (!content[len] || !content || !*content)
		return (ft_strdup(""));
	i = len;
	while (content[len])
		len++;
	len = len - i;
	rest = (char *) ft_calloc((len + 1), sizeof(char));
	if (!rest)
		return (printf("Allocation failed\n"), NULL); //
	len = 0;
	while (content[i])
		rest[len++] = content[i++];
	return (rest);
}

int	join_all(t_input **cur, char *start, char *end, char *var)
{
	char *temp;
	char *joint;

	joint = ft_strjoin(start, var);
	if (!joint)
		return (free(start), free(var), free(end), 1);
	free(start);
	free(var);
	temp = ft_strjoin(joint, end);
	if (!temp)
		return (1);
	free(joint);
	joint = temp;
	free(end);
	free((*cur)->content);	
	(*cur)->content = ft_strdup(joint);
	free(joint);
	return 0;
}

char *extract_var(char **envp, char *var)
{
	char *value;
	char *temp;
	int i;

	i = 0;
	if (!var || !*var)
		return (free(var), ft_strdup(""));

	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
		{
			temp = ft_strchr(envp[i], '=') + 1;
			value = ft_strdup(temp);
			return(free(var), value);
		}
		else
			i++;
	}
	return (free(var), ft_strdup(""));
	
}

char	*search_var(char *content, char *var)
{
	char *temp;
	int	len;
	
	len = ft_strlen(content);
	temp = content;
	while(temp - content <= len)
	{
		temp = ft_strnstr(temp, var, ft_strlen(var));
		if (check_quotes(content, temp - content) != 1)
			break;
		temp++;
	}
	return (temp);
}

int	expand_var(t_input **cur, t_data *data)
{
	char *start;
	char *var;
	char	*end;

	if (stop((*cur)->content) == 0)
		return 0;
	start = save_start((*cur)->content);
	if (!start)
		return (1);
	var = save_var(&(*cur)->content[start_len((*cur)->content)]);
	if (!var)
		return (free(start), 1);
	end = save_rest(search_var((*cur)->content, var), var);
	if (!end)
		return (free(start), free(var), 1);
	var = extract_var(data->envp, var);
	if (join_all(cur, start, end, var) == 1)
		return 1;	//error or wat ?
	if (ft_strchr((*cur)->content, '$') != 0)
		expand_var(cur, data);
	return 0;
}

int	find_ev(t_input *first, t_data *data)
{
	t_input	*cur;

	cur = first;
	while(cur)
	{
		if (ft_strchr(cur->content, '$'))
			expand_var(&cur, data);
/* 		if (ft_strchr(cur->content, '\'') || ft_strchr(cur->content, '"'))
			remove_useless_quotes(cur->content); */
		cur = cur->next;
		if (cur == first)
			break ;
	}
	return 0;
}
