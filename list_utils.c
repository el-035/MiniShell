#include"minishell.h"

t_input	*make_new_node(char *content, int pos)
{
	t_input	*node;

	node = (t_input *)malloc(sizeof(t_input));
	if (!node)
		return (NULL);
	init_input(node);
	node->content = content;
	node->position = pos;
	return (node);
}

t_input	*add_new(char *content, int pos, t_input *prev)
{
	t_input	*node;

	node = make_new_node(content, pos);
	if (node == NULL)
		return (write(2, "Error: node wasn't created\n", 27), NULL); //handle later
	prev->next = node;
	node->prev = prev;
	return (node);
}

int	list_size(t_input *first)
{
	int	size;
	t_input *cur;

	size = 1;
	if (!first)
		return (0);
	cur = first->next;
	while (cur != first)
	{
		cur = cur -> next;
		size++;
	}
	return (size);
}