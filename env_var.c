#include"minishell.h"

char *save_start(char *content)
{
	int i;
	int len;
	char *start;

	i = 0;
	len = 0;
	while (content[len] != '$')
		len++;
	if (len == 0)
		return (ft_strdup(""));
	start = (char *) ft_calloc((len + 1), sizeof(char));
	if (!start)
		return (printf("Allocation failed\n"), NULL); //
	while (i < len)
	{
		start[i] = content[i];
		i++;
	}
	return (start);
}

char	*extract_var(char *content)
{
	int i;
	int len;
	char *var;

	i = -1;
	len = 0;
	while (content[len] && (ft_isalnum(content[len]) != 0 || content[len] == '_'))
		len++;
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

int	save_var(t_input **cur, char *start, char *end, char *var)
{
	char *temp;
	char *value;

	value = getenv(var);		//what if its not
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
	while (content[i] != '$')
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

int	expand_var(t_input **cur)
{
	char *start;
	char *var;
	char	*end;
	//int		count;


	if (ft_strchr((*cur)->content, '"') != 0 || ft_strchr((*cur)->content, '\'') != 0)
	{
		if (check_quotes((*cur)->content) == 1)
			return 0;
	}
	/* if (ft_strncmp((*cur)->content, "$?", 2) == 0)	//find better way it could be not first
		return (5); //idk handle this :( 	also handle more than one $ */
	start = save_start((*cur)->content);
	if (!start)
		return (1);
	var = extract_var(ft_strchr((*cur)->content, '$') + 1);
	if (!var)
		return (free(start), 1);
	end = save_rest(ft_strchr((*cur)->content, '$') + 1, var);
	if (!end)
		return (free(start), free(var), 1);
	if (save_var(cur, start, end, var) == 1)
		return 1;
	if (ft_strchr((*cur)->content, '$') != 0)
		expand_var(cur);
	return 0;
}

int	find_ev(t_input *first)
{
	t_input	*cur;

	cur = first;
	while(cur)
	{
		if (ft_strchr(cur->content, '$'))	//handle $$ and /$
			expand_var(&cur);
		cur = cur->next;
		if (cur == first)
			break ;
	}
	return 0;
}