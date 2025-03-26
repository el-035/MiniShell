#include"minishell.h"

//HOW THE SHELL WORKS
//first checks how many commands there are
//each command is a token
//checks the syntax of all, if any error will not start
//evaluate variables??
//it now checks if the token represents a build in command or external one
//if external it goes to the path
//sets up redirections including pipes (needs to be ready before command starts)
//execution starts


/* 
Variable expansion (if you want to handle $VARIABLE):
Expand environment variables ($HOME, $PATH, etc.)
Handle special cases like $? (exit status)
Command identification:

Check if the command is a built-in (cd, echo, etc.) or an external command.
If it's external, search for it in the PATH.
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


int	pipe_syntax(t_input *cur, t_input *first)
{
	if (cur == first || cur->next == first)
		return (printf("Syntax error\nPipe cannot be at beginning or end\n"), 1);
	if (cur->next != first && cur->next->type == PIPE)
		return (printf("Syntax error\nTwo consecutive pipes\n"), 1);
	if (cur->next != first && cur->next->type != ARG && cur->next->type != CMD)
		return (printf("Syntax error\nPipes must be followed by commands or arguments\n"), 1);
	return 0;
}

int redir_syntax(t_input *cur, t_input *first)
{
	if (cur == first || cur->next == first)
		return (printf("Syntax error\nRedirection cannot be at beginning or end\n"), 1);
	if (cur->next->type == REDIR_APPEND || cur->next->type == REDIR_IN || cur->next->type == REDIR_OUT || cur->next->type == HERE_DOC)
		return (printf("Syntax error\nTwo consecutive redirections\n"), 1);
	if (cur->next != first && cur->next->type == PIPE)
		return (printf("Syntax error\nPipe following redirection\n"), 1);
	if (cur->next != first && cur->next->type != ARG && cur->next->type != CMD)
		return (printf("Syntax error\nRedirections must be followed by commands or arguments\n"), 1);
	//Redirection needs a valid file/token after it:
	return 0;
}

int quotes_syntax(t_input *cur)
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
		return(printf("Syntax error\nUnclosed quotes\n"), 1);
	return 0;
}

int	syntax_check(t_input *first)
{
	t_input *cur;
	int		size;

	cur = first;
	size = list_size(first) - 1;
	while (size-- >= 0)
	{
		if (cur->type == PIPE && pipe_syntax(cur, first) == 1)
			return (1);
		if ((cur->type == REDIR_APPEND || cur->type == REDIR_IN || cur->type == REDIR_OUT || cur->type == HERE_DOC) && redir_syntax(cur, first) == 1)
			return (1);
		if ((ft_strchr(cur->content, '\'') != NULL || ft_strchr(cur->content, '"') != NULL) && quotes_syntax(cur) == 1)
			return (1);
		//Redirection needs a valid file/token after it:
		//Invalid Environment Variables??
		cur = cur->next;
	}
	return 0;
}

int is_red_or_pipe(t_input *first)
{
	if (ft_strncmp(first->content, "<", 2) == 0)
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
	cur = (*first)->next;
	
	while (cur != *first)
	{
		if (cur->prev->type == CMD && is_red_or_pipe(cur) == 0)
		cur->type = ARG;
		else if (cur->prev->type == PIPE)
		cur->type = CMD;
		else if (cur->prev->type == REDIR_APPEND || cur->prev->type == REDIR_IN || cur->prev->type == REDIR_OUT || cur->prev->type == HERE_DOC)
		cur->type = ARG;
		is_red_or_pipe(cur);	//double check this
		cur = cur->next;
	}
	return(syntax_check(*first));
}


