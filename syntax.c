#include "minishell.h"

int	more_syntax(t_input *cur)
{
	if (is_red(cur) == 1 && cur->next->type == REDIR_OUT)
		return (syntax_err(), 1);
	if (is_red(cur) == 1 && cur->next->type == REDIR_IN)
		return (syntax_err(), 1);
	if (is_red(cur) == 1 && cur->next->type == REDIR_APPEND)
		return (syntax_err(), 1);
	if (is_red(cur) == 1 && cur->next->type == HERE_DOC)
		return (syntax_err(), 1);
	if (cur->type == PIPE && cur->next->type == PIPE)
		return (syntax_err(), 1);
	if (is_red(cur) == 1 && cur->next->type == PIPE)
		return (syntax_err(), 1);
	if (ft_strncmp(cur->content, ">>>", 3) == 0 || ft_strncmp(cur->content,
			"<<<", 3) == 0)
		return (syntax_err(), 1);
	if (ft_strncmp(cur->content, "|||", 3) == 0)
		return (syntax_err(), 1);
	return (0);
}

int	check_nl(t_input *first)
{
	if (is_red(first) == 1 && !first->next)
		return (syntax_err(), 1);
	if (first->type == PIPE)
		return (syntax_err(), 1);
	if (!first->prev)
		return (0);
	if (is_red(first->prev) == 1)
		return (syntax_err(), 1);
	return (0);
}

int	syntax_check(t_input *first)
{
	t_input	*cur;
	int		size;

	cur = first;
	size = list_size(first) - 1;
	if (check_nl(first) != 0)
		return (1);
	while (size-- >= 0)
	{
		if (more_syntax(cur) != 0)
			return (1);
		if (check_quotes(cur->content, ft_strlen(cur->content)) != 0)
			return (printf("Unexpected end of file\n"), return_exit_code(2), 1);
		cur = cur->next;
	}
	return (0);
}

int	assign_type(t_input **first)
{
	t_input	*cur;

	if ((*first)->position == 0 && is_red_or_pipe(*first) == 0)
		(*first)->type = CMD;
	if ((*first)->next)
		cur = (*first)->next;
	else
		cur = *first;
	while (cur != *first)
	{
		if (cur->prev->type == CMD && is_red_or_pipe(cur) == 0)
			cur->type = ARG;
		else if (cur->prev->type == PIPE)
			cur->type = CMD;
		else if (is_red(cur->prev) == 1)
			cur->type = ARG;
		is_red_or_pipe(cur);
		if (cur->type == UNKNOWN)
			cur->type = ARG;
		cur = cur->next;
	}
	return (syntax_check(*first));
}
