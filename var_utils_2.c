#include "minishell.h"

t_input	*beginning(t_input *cur, char *start, char *exp, int f_b) //
{
	if (!start || start[0] == '\0')
	{
		cur->content = ft_strdup(exp);
		cur->exp = 0;
	}
	else if (f_b == 1)
	{
		cur->content = ft_strdup(start);
		if (!cur->content)
			return (NULL);
		cur = add_node(cur, exp);
		if (!cur)
			return (NULL);
		cur->exp = 0;
	}
	else
	{
		cur->content = ft_strjoin(start, exp);
		cur->exp = ft_strlen(start);
	}
	if (!cur->content)
		return (NULL);
	return (cur);
}

t_input	*end(t_input *cur, char *next, int f_e)
{
	char	*tmp;

	if (next && next[0] != '\0')
	{
		if (f_e == 1)
		{
			cur = add_node(cur, next);
			if (!cur)
				return (NULL);
		}
		else
		{
			tmp = cur->content;
			cur->content = ft_strjoin(tmp, next);
			if (!cur->content)
				return (NULL);
			cur->exp = 0 - ft_strlen(tmp);
			free(tmp);
		}
	}
	return (cur);
}

t_input	*middle(t_input *cur, char **split)
{
	int	len;
	int	i;

	len = arr_len(split);
	i = 1;
	while (i < len - 1)
	{
		cur = add_node(cur, split[i++]);
		if (!cur)
			return (NULL);
		cur->exp = 0;
	}
	if (len > 1)
	{
		cur = add_node(cur, split[len - 1]);
		if (!cur)
			return (NULL);
		cur->exp = 0;
	}
	return (cur);
}

t_input	*empty(t_input *cur, char *start, char *next, char *exp) //
{
	if (exp[0] == '\0')
	{
		cur->content = ft_strjoin(start, next);
		if (!cur->content)
			return (NULL);
		if (cur->content[0] == '\0')
			cur->exp = 0;
		return (cur);
	}
	else if (count_word(exp) == 0)
	{
		cur->content = ft_strdup(start);
		cur = add_node(cur, next);
		return (cur);
	}
	return (cur);
}

t_input	*add_node(t_input *cur, char *content) //
{
	t_input	*new;

	if (!content || !*content)
		return (NULL);
	new = (t_input *)malloc(sizeof(t_input));
	if (!new)
		return (NULL);
	ft_memset(new, 0, sizeof(t_input));
	init_input(new);
	new->content = ft_strdup(content);
	if (!new->content)
		return (free(new), NULL);
	cur->next->prev = new;
	new->next = cur->next;
	new->prev = cur;
	cur->next = new;
	return (new);
}
