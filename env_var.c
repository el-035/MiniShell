#include"minishell.h"

int return_len_content(char *content)
{
	int len = 0;

	while (content[len])
	{
		while (content[len] && content[len] != '$')
			len++;
		if (!content[len])
			break ;
		if (content[len + 1] && (content[len + 1] == '$' || content[len + 1] == '?'))
			len = len + 2;
		if (!content[len])
			break ;
		if (content[len] == '$' && (content[len + 1] != '?' || content[len + 1] != '?'))
			break ;
	}
	return len;
	
}

char *save_start(char *content)
{
	int i;
	int len;
	char *start;

	i = 0;
	len = return_len_content(content);
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
		if (ft_isalnum(content[len]) || content[len] == '_')
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
	if (!content[len])
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
	char *value;

	value = var;		//useless?
	value = ft_strjoin(start, value);
	if (!value)
		return (free(start), free(var), free(end), 1);
	free(start);
	temp = ft_strjoin(value, end);
	free(value);
	value = temp;
	free(end);
	if (!value)
		return (free(var), 1);
	free((*cur)->content);	
	(*cur)->content = ft_strdup(value);
	free(var);
	free(value);
	return 0;
}

int	check_quotes(char *content)
{
	int i;
	int f_single;
	int f_double;

	i = 0;
	f_double = 0;
	f_single = 0;
	while (content[i] && content[i] != '$')
	{
		if (content[i] == '\'' && f_single != 1 && f_double != 1)
			f_single = 1;
		else if (content[i] == '\'' && f_single == 1 && f_double != 1)
			f_single = 0;
		if (content[i] == '"' && f_double != 1 && f_single != 1)
			f_double = 1;
		else if (content[i] == '"' && f_double == 1 && f_single != 1)
			f_double = 0;
		i++;
	}
	if (f_single == 1)
		return 1;
	return 0;
}

int	stop_exp(char *content)
{
	int i;
	int len = ft_strlen(content);

	i = 0;
	while (i < len)
	{
		if (content[i] && content[i + 1] && content[i] == '$' && (content[i + 1] == '?' || content[i + 1] == '$'))
		{
			i += 2;
			if (!content[i])
				return 0;
		}
		else if (content[i] && content[i] == '$')
			return 1;
		/* else if ((content[i] == '\'' || content[i] == '"') && check_quotes(&content[i]) == 1)
			return 1; */
		else
			i++;
		//ceck if in single quotes 
	}
	return (0);
}

char *extract_var(char **envp, char *var)
{
	char *value;
	char *temp;
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
		{
			temp = ft_strchr(envp[i], '=') + 1;
			value = ft_strdup(temp);
			printf("value is: %s\n", value);
			return(free(var), value);
		}
		else
			i++;
	}

	return (free(var), ft_strdup(""));
	
}

int	expand_var(t_input **cur, t_data *data)
{
	char *start;
	char *var;
	char	*end;
	//make a check, if only $$ or $? are present, or things in quotes then return

	if (stop_exp((*cur)->content) == 0)
		return 0;
	start = save_start((*cur)->content);
	if (!start)
		return (1);
	var = save_var(&(*cur)->content[return_len_content((*cur)->content)]);
	if (!var)
		return (free(start), 1);
	end = save_rest(strstr((*cur)->content, var), var);	//forbidden function!!!!	STRSTR
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
/* 		if (ft_strchr(cur->content, '\'') || ft_strchr(cur->content, '"'))
			remove_useless_quotes(cur->content); */
		if (ft_strchr(cur->content, '$'))	//handle $$ and /$
			expand_var(&cur, data);
		cur = cur->next;
		if (cur == first)
			break ;
	}
	return 0;
}
