#include "minishell.h"

int handle_heredoc(t_input *input, t_data *data)
{
	t_input *cur;
	t_input *start;

	cur = input;
	start = input;
	while (1)
	{
		if (cur->type == HERE_DOC)
			exec_heredoc();
		curr = cur->next;
		if (cur == start)
			break ;
	}
	return (0);
}
