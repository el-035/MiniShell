#include"minishell.h"

t_input	*make_new_node(char *content, int pos)
{
	t_input	*node;

	node = (t_input *)malloc(sizeof(t_input));
	if (!node)
		return (NULL);
	node->content = content;
	node->position = pos;
	node->next = NULL;
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
