#include "minishell.h"

void	init_input(t_input *first)
{
	first->content = NULL;
	first->type = UNKNOWN;
	first->position = -1;
	first->next = first;
	first->prev = first;
	first->is_builtin = -1;
	first->exp = -1;
}

int	save_input(char *line, t_input **first)
{
	t_input	*cur;
	char	**split;
	int		pos;

	pos = 0;
	split = mini_split(line);
	if (!split)
		return (0);
	*first = make_new_node(split[pos], pos);
	if (!*first)
		return (free_split(split), fail_mall(), 0);
	cur = *first;
	while (split[++pos])
	{
		cur = add_new(split[pos], pos, cur);
		if (!cur)
			return (free_split(split), free_list(*first), fail_mall(), 0);
	}
	if (pos > 1)
	{
		cur->next = *first;
		(*first)->prev = cur;
	}
	return (free_split(split), 1);
}

t_input	*make_new_node(char *content, int pos)
{
	t_input	*node;

	node = (t_input *)malloc(sizeof(t_input));
	if (!node)
		return (NULL);
	init_input(node);
	node->content = ft_strdup(content);
	if (!node->content) // fix
	{
		free(node);
		return (NULL);
	}
	node->position = pos;
	return (node);
}

t_input	*add_new(char *content, int pos, t_input *prev)
{
	t_input	*node;

	node = make_new_node(content, pos);
	if (node == NULL)
		return (write(2, "Error: node wasn't created\n", 27), NULL);
	// handle later
	prev->next = node;
	node->prev = prev;
	return (node);
}

int	list_size(t_input *first)
{
	int		size;
	t_input	*cur;

	size = 1;
	if (!first)
		return (0);
	if (!first->next)
		return (1);
	cur = first->next;
	while (cur != first)
	{
		cur = cur->next;
		size++;
	}
	return (size);
}
