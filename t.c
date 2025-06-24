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
/* 	if (type == ENV_VAR)
		return "ENV_VAR"; */
	return "UNKNOWN";
}


void	test_print(t_input *first)
{
	t_input *cur;
	cur = first;
	
	if (!cur->next)
	{

		printf("node %d, cur: %p, next: %p, content: %s: type: %s ex:%d\n", cur->position, cur, cur->next, cur->content, get_type_str(cur->type), cur->exp/* , cur->cmd_path */);

		
		//printf("node %d, content: %s: type:%s\n", cur->position, cur->content, get_type_str(cur->type));
		return ;
	}

	while(cur)
	{
		//printf("cur: %p prev: %p\n", cur, cur->prev);
		//printf("node %d, content: %s: type:%s\n", cur->position, cur->content, get_type_str(cur->type));

		printf("node %d, cur: %p, next: %p, content: %s: type: %s ex:%d\n", cur->position, cur, cur->next, cur->content, get_type_str(cur->type), cur->exp/* , cur->cmd_path */);
		cur = cur->next;
		if (cur == first)
			break;
	}
	//printf("cur: %p prev: %p\n", cur, cur->prev);

//	printf("node %d, content: %s:  type:%s\n", cur->position, cur->content, get_type_str(cur->type));
	//printf("node %d, content: %s: type: %s bi:%d\n", cur->position, cur->content, get_type_str(cur->type), cur->is_builtin);

}