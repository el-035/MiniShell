#include "minishell.h"

int	count_word(char *content)
{
	int	wc;
	int	start;

	wc = 0;
	start = 0;
	while (content[start])
	{
		if (content[start] != ' ' && content[start] != '\t'
			&& content[start] != '\n')
			start++;
		else
		{
			wc++;
			start++;
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
		new->type = CMD;
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

int	ft(t_input *cur, int i)
{
	char	**split;
	int		count;
	char	*tmp;

	tmp = cur->content;
	if (count_word(cur->content) < 2)
		return (0);
	split = ft_split(cur->content, ' ');
	if (!split)
		return (1);
	count = arr_len(split);
	if (count == 1)
		return (0);
	if (add_node(cur, cur->next, count - 1) != 0)
		return (free_split(split), 1);
	free(cur->content);
	while (i < count)
	{
		cur->content = ft_strdup(split[i++]);
		if (!cur->content)
			return (free_split(split), 1);
		cur = cur->next;
	}
	return (free_split(split), 0);
}

int	exp_split(t_input *first)
{
	t_input	*cur;
	int		i;

	i = 0;
	cur = first;
	while (cur)
	{	
		if (cur->exp != -1)
		{
			//cur->exp = 2;
			if (ft(cur, i) != 0)
			return (fail_mall(), 1);
		}
		cur = cur->next;
		if (cur == first)
		break ;
	}
	return (0);
}
