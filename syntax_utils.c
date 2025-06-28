#include "minishell.h"

void	syntax_err(void)
{
	write(2, "bash: syntax error near unexpected token\n", 42);
	return_exit_code(2);
}

int	is_red(t_input *cur)
{
	if (cur->type != REDIR_APPEND && cur->type != HERE_DOC
		&& cur->type != REDIR_IN && cur->type != REDIR_OUT)
		return (0);
	return (1);
}

int	is_red_or_pipe(t_input *first)
{
	if (ft_strncmp(first->content, ">>", 3) == 0)
		return (first->type = REDIR_APPEND, 1);
	else if (ft_strncmp(first->content, "<<", 3) == 0)
		return (first->type = HERE_DOC, 1);
	else if (ft_strncmp(first->content, "<", 1) == 0)
		return (first->type = REDIR_IN, 1);
	else if (ft_strncmp(first->content, ">", 2) == 0)
		return (first->type = REDIR_OUT, 1);
	else if (ft_strncmp(first->content, "|", 2) == 0)
		return (first->type = PIPE, 1);
	else
		return (0);
}
