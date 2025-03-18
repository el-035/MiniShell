#include"minishell.h"

const char *get_type_str(enum e_type type)
{
	if (type == CMD)
		return "CMD";
	if (type == ARG)
		return "ARG";
	if (type == PIPE)
		return "PIPE";
	if (type == REDIR_IN)
		return "REDIR_IN";
	if (type == REDIR_OUT)
		return "REDIR_OUT";
	if (type == REDIR_APPEND)
		return "REDIR_APPEND";
	if (type == HERE_DOC)
		return "HERE_DOC";
	if (type == ENV_VAR)
		return "ENV_VAR";
	if (type == SUBSHELL)
		return "SUBSHELL";
	return "UNKNOWN";
}


void	test_print(t_input *first)
{
	t_input *cur;
	cur = first;
	 
	while(cur->next != first)
	{
		printf("node %d, content: %s: type:%s\n", cur->position, cur->content, get_type_str(cur->type));
		cur = cur->next;
	}
	printf("node %d, content: %s:  type:%s\n", cur->position, cur->content, get_type_str(cur->type));

}