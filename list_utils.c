/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <efittant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:03:40 by efittant          #+#    #+#             */
/*   Updated: 2025/07/12 04:46:14 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_input(t_input *first)
{
	first->content = NULL;
	first->type = UNKNOWN;
	first->position = -1;
	first->next = first;
	first->prev = first;
	first->is_builtin = 0;
	first->exp = INT_MIN;
}

int	save_input(char *line, t_input **first, int pos)
{
	t_input	*cur;
	char	**split;

	split = mini_split(line);
	if (!split)
		return (fail_mall(), 0);
	if (!*split)
		return (free_split(split), 0);
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
	return (free_split(split), free(line), 1);
}

t_input	*make_new_node(char *content, int pos)
{
	t_input	*node;

	node = (t_input *)malloc(sizeof(t_input));
	if (!node)
		return (NULL);
	init_input(node);
	node->content = ft_strdup(content);
	if (!node->content)
		return (free(node), NULL);
	node->position = pos;
	return (node);
}

t_input	*add_new(char *content, int pos, t_input *prev)
{
	t_input	*node;

	node = make_new_node(content, pos);
	if (node == NULL)
		return (NULL);
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
