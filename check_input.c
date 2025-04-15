#include"minishell.h"

//HOW THE SHELL WORKS
//first checks how many commands there are
//each command is a token
//checks the syntax of all, if any error will not start
//evaluate variables
//it now checks if the token represents a build in command or external one
//if external it goes to the path
//sets up redirections including pipes (needs to be ready before command starts)
//execution starts

/*

Set up redirections and pipes:
Open/close file descriptors for redirections (<, >, >>)
Set up pipes between commands if needed
Fork and execute:

If built-in → execute directly in the parent process
If external → fork, execute in the child process, and wait for the result
Handle signals:

Handle CTRL+C, CTRL+D, CTRL+\
Restore terminal state if needed
Clean up:
Free memory and close file descriptors */


int is_red(t_input *cur)
{
	if (cur->type != REDIR_APPEND && cur->type != HERE_DOC && cur->type != REDIR_IN && cur->type != REDIR_OUT)
		return (0);
	return 1;
}

int more_syntax(t_input *cur, t_input *first)	//newline erorr
{
	(void)*first;		//
	if (is_red(cur) == 1 && cur->next->type == REDIR_OUT)
		return (write(2, " syntax error near unexpected token `>'\n", 40), return_exit_code(2), 1);
	
	if (is_red(cur) == 1 && cur->next->type == REDIR_IN)
		return (write(2, " syntax error near unexpected token `<'\n", 40), return_exit_code(2), 1);

	if (is_red(cur) == 1 && cur->next->type == REDIR_APPEND)
		return (write(2, " syntax error near unexpected token `>>'\n", 40), return_exit_code(2), 1);

	if (is_red(cur) == 1 && cur->next->type == HERE_DOC)
		return (write(2, " syntax error near unexpected token `<<'\n", 40), return_exit_code(2), 1);
	if (cur->type == PIPE && cur->next->type == PIPE)
		return (write(2, " syntax error near unexpected token `|'\n", 40), return_exit_code(2), 1);
	if ((cur->type == REDIR_APPEND || cur->type == REDIR_IN || cur->type == REDIR_OUT || cur->type == HERE_DOC) && cur->next->type == PIPE)
		return (write(2, " syntax error near unexpected token `|'\n", 40), return_exit_code(2), 1);
	return 0;
}

int quotes_syntax(t_input *cur)	//idk 
{
	int i = 0;
	int	s = 0;
	int d = 0;

	while(cur->content[i])
	{
		if (cur->content[i] == '\'')
			s++;
		if (cur->content[i] == '"')
			d++;
		i++;
	}
	if (s % 2 != 0 || d % 2 != 0)
		return(printf("Unexpected end of file\n"), return_exit_code(2), 1);
	return 0;
}

int check_nl(t_input *first)
{
	if (first->type == REDIR_APPEND || first->type == REDIR_IN || first->type == REDIR_OUT || first->type == HERE_DOC)
		return (write(2, " syntax error near unexpected token `newline'\n", 46), return_exit_code(2), 1);
	if (first->type == PIPE)
		return (write(2, " syntax error near unexpected token `|'\n", 40), return_exit_code(2), 1);
	if (!first->prev)
		return (0);

	if (first->prev->type == REDIR_APPEND || first->prev->type == REDIR_IN || first->prev->type == REDIR_OUT || first->prev->type == HERE_DOC)
		return (write(2, " syntax error near unexpected token `newline'\n", 46), return_exit_code(2), 1);
	return 0;
	//unclosed quotes or parenthesis
}

int	syntax_check(t_input *first)
{
	t_input *cur;
	int		size;
	int		exit;

	cur = first;
	size = list_size(first) - 1;
	exit = check_nl(first);
	if (exit != 0)
		return (exit);
	while (size-- >= 0)
	{
		exit = more_syntax(cur, first);
		if (exit != 0)
			return (exit);
		exit = quotes_syntax(cur);
		if ((ft_strchr(cur->content, '\'') != NULL || ft_strchr(cur->content, '"') != NULL) && exit != 0)
			return (exit);
		cur = cur->next;
	}
	return 0;
}

int is_red_or_pipe(t_input *first)
{
	if (ft_strncmp(first->content, "<", 1) == 0)
		return (first->type = REDIR_IN, 1);
	else if (ft_strncmp(first->content, ">", 2) == 0)
		return (first->type = REDIR_OUT, 1);
	else if (ft_strncmp(first->content, ">>", 3) == 0)
		return (first->type = REDIR_APPEND, 1);
	else if (ft_strncmp(first->content, "<<", 3) == 0)
		return (first->type = HERE_DOC, 1);
	else if (ft_strncmp(first->content, "|", 2) == 0)
		return (first->type = PIPE, 1);
	else
		return (0);
}

int	assign_type(t_input **first)
{
	t_input *cur;

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
		else if (cur->prev->type == REDIR_APPEND || cur->prev->type == REDIR_IN || cur->prev->type == REDIR_OUT || cur->prev->type == HERE_DOC)
			cur->type = ARG;
		is_red_or_pipe(cur);	//double check this
		if (cur->type == UNKNOWN)	//fixxxxxxxx bitchhhh
			cur->type = ARG;
		cur = cur->next;
	}
	return(syntax_check(*first));
}
