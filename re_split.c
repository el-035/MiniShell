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

int	total_new_nodes(char *exp, char *next, char *start)
{
	int nodes;
	//int count;

	nodes = count_word(exp);
	if (is_space(exp[0]) == 1)
	{
		if (start && start[0] != '\0')
			nodes ++;
	}
	if (is_space(exp[ft_strlen(exp) - 1]) == 1)
	{
		if (next && next[0] != '\0')
			nodes ++;
	}
	return (nodes - 1);
}
int fill_first (t_input *cur, char *exp, char **split, char *start)
{
	if (start && start[0] != '\0')
	{
		if (is_space(exp[0]) == 1)
			cur->content = ft_strdup(start);
		else
			cur->content = ft_strjoin(start, split[0]);
	}
	else
		cur->content = ft_strdup(split[0]);
	//printf("filled first: %s %p\n", cur->content, cur);
	return 0;
}

int fill_middle (t_input *cur, char *exp, char **split, char *start)
{
	int i = 0;
	int count = count_word(exp);

	if ((start && start[0] != '\0' && is_space(exp[0]) != 1) || (!start && start[0] == '\0'))
	{
		i++;
	}
	cur = cur->next;
	if (!split[i])
	{
		return 0;
	}
	while (i < count && split[i])
	{
		
		cur->content = ft_strdup(split[i]);
		//printf("filled middle: %s %p\n", cur->content, cur);
		if (!cur->content)
			return (free_split(split), 1);
		/* if (i == count -1)
			break ; */
		cur = cur->next;
		i++;
	}
	return 0;
}

int fill_end(t_input *cur, char *exp, char **split, char *next)
{
	if (next && next[0] != '\0')
	{
		if (is_space(exp[ft_strlen(exp) - 1]) == 1)
		{
			cur->content = ft_strdup(split[count_word(exp) - 1]);
			cur = cur->next;
			cur->content = ft_strdup(next);
		}
		else
		{
			cur->content = ft_strjoin(split[count_word(exp) - 1], next);
		}
	}
	else
	{
		cur = cur->next;
		cur->content = ft_strdup(split[count_word(exp) - 1]);
	}
	//printf("filled last: %s %p\n", cur->content, cur);

	return 0;
}
int	ft(t_input *cur, char *exp, char *next, char *start)
{
	char	**split;
	int		nodes;
/* 	int		count;

	count = count_word(exp); */
	/* //printf("count%d", count); */
	split = space_split(exp);
	if (!split)
		return (1);
	nodes = total_new_nodes(exp, next, start);
	
	if (nodes > 0 && add_node(cur, cur->next, nodes) != 0)
		return (free_split(split), 1);

	//fix the start
	//free(cur->content);
	fill_first(cur, exp, split, start);
	
	//loop the middle
	fill_middle(cur, exp, split, start);
	while (--nodes > 0)
		cur = cur->next;
	//fix the end
	fill_end(cur, exp, split, next);
	return (free_split(split), 0);
}
/* 
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
} */
