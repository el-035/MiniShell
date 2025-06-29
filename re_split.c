#include "minishell.h"

int	count_word(char *content)
{
	int	 i;
	int	 wc;

	i = 0;
	wc = 0;
	if (!content)
		return (0);
	while (content[i])
	{
		while (content[i] && is_space(content[i]) == 1)
			i++;
		if (content[i] && is_space(content[i]) == 0)
		{
			wc++;
			while (content[i] && is_space(content[i]) == 0)
				i++;
		}
	}
	return (wc);
}

void	init_node(t_input *cur, t_input *tmp, t_input *new, int i)
{
	ft_memset(new, 0, sizeof(t_input));
	init_input(new);
	new->exp = 2;
	if (i == 0)
	{
		cur->next = new;
		new->prev = cur;
		new->type = ARG;
	}
	else
	{
		tmp->next = new;
		new->prev = tmp;
		new->type = ARG;
	}
	tmp = new;
}

int	add_node(t_input *cur, t_input *next, int count)
{
	t_input	*new;
	t_input	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	cur->type = CMD;
	while (i < count)
	{
		new = (t_input *)malloc(sizeof(t_input));
		if (!new)
			return (1);
		init_node(cur, tmp, new, i);
		tmp = new;
		i++;
	}
	tmp->next = next;
	next->prev = tmp;
	return (0);
}

int	ft(t_input *cur)
{
	char	**split;
	int		count;
	int		i;

	i = 0;
	count = count_word(cur->content);
	if (count < 2)
		return (0);
	split = space_split(cur->content);
	if (!split)
		return (1);	
	if (add_node(cur, cur->next, count - 1) != 0)
		return (free_split(split), 1);
	free(cur->content);
	while (i < count && split[i])
	{
		cur->content = ft_strdup(split[i]);
		if (!cur->content)
			return (free_split(split), 1);
		cur = cur->next;
		i++;
	}
	return (free_split(split), 0);
}

int	exp_split(t_input *first)
{
	t_input	*cur;

	cur = first;
	while (cur)
	{
		if (cur->exp != -1)
		{
			if (ft(cur) != 0)
				return (fail_mall(), 1);
		}
		cur = cur->next;
		if (cur == first)
			break ;
	}
	return (0);
}
