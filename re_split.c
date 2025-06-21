#include "minishell.h"

/* void init_new(t_input *new, t_input *cur, t_input *first)
{
	int i;
	t_input *temp;
	
	new->prev = cur;
	if (cur->next != cur)
	{
		new->next = cur->next;
		cur->next->prev = new;
	}
	else
	{
		new->next = cur;
		cur->prev = new;
	}
	cur->next = new;
	new->type = ARG;
	cur->type = CMD;
	i = cur->position;
	new->position = ++i;
	temp = new->next;
	while (temp != first)
	{
		temp->position = ++i;
		temp = temp->next;
	}
}

int	count_word(char *content, int start)
{
	int wc;

	wc = 0;
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

char **get_start(char *content, int start)
{
	char *beg;
	int i;

	i = 0;
	while (content[start] && content[start] != ' ' && content[start] != '\t' && content[start] != '\n')
		start++;
	beg = (char *) ft_calloc(start + 1, sizeof(char));
	if (!beg)
		return (fail_mall(), NULL);	//
	while(i <= start)
	{
		beg[i] = content[i];
		i++;
	}
	return (beg);
}

int	add_node(t_input *cur, t_input *first)
{
	t_input *new;
	char *beg;
	char *end;
	int i;
	int j;

	i = cur->exp;
	if (count_word(cur->content, i) < 2)
		return 0;
	while (cur->content[i] && cur->content[i] != ' ' && cur->content[i] != '\t' && cur->content[i] != '\n')
		i++;
	if (!cur->content[j + 1])
		return 0;
	new = (t_input *)malloc(sizeof(t_input));
	if (!new)
		return (fail_mall(), 1);	//
	init_input(new);
	init_new(new, cur, first);
	
	
	beg = get_start(cur->content, cur->exp);
	if (!beg)
		return (fail_mall(), 1);	//
	
	end = get_rest(cur->content, cur->exp)

	cur->exp = -1;
	free(cur->content);
	cur->content = beg;
	new->content = end;
	return 0;
}

int	exp_split(t_input *first)
{
	t_input *cur;

	cur = first;
	while (cur)
	{
		if (cur->exp != -1)
		{
			if (add_node(cur, first) != 0)
				return 1;
		}
		cur = cur->next;
		if (cur == first)
			break ;
	}
	return 0;
} */