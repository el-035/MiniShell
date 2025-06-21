#include "minishell.h"

int	count_word(char *content)
{
	int wc;
	int start;

	wc = 0;
	start = 0;
	while(content[start])
	{
		if (content[start] != ' ' && content[start] != '\t' && content[start] != '\n')
			start++;
		else
		{
			wc++;
			start++;
		}
	}
	return (wc);
}
void init_node(t_input *cur, t_input *tmp, t_input *new, int i)
{
	ft_memset(new, 0, sizeof(t_input));
	init_input(new);
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
	t_input *new;
	t_input *tmp;
	int i;

	i = 0;
	tmp  = NULL;
	while (i < count)
	{
		new = (t_input *)malloc(sizeof(t_input));
		if (!new)
			return (fail_mall(), 1);
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
	char **split;
	int	i;
	int count;

	i = 0;
	if (count_word(cur->content) < 2)
		return 0;
	split = mini_split(cur->content);
	if (!split)
		return (fail_mall(), 1); //check
	count = arr_len(split);
	if (count == 1)
		return 0;
	add_node(cur, cur->next, count - 1);
	while (i < count)
	{
		cur->content = ft_strdup(split[i++]);		//protect
		cur = cur->next;
	}
	return 0;
}

int	exp_split(t_input *first)
{
	t_input *cur;

	cur = first;
	while (cur)
	{
		if (cur->dq_var != NULL)
		{
			if (ft(cur) != 0)
				return 1;
		}
		cur = cur->next;
		if (cur == first)
			break ;
	}
	return 0;
} 