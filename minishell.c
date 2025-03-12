#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void init_input(t_input *first)
{
	//printf("test init\n");
	
	first->content = NULL;
	first->type = NULL;
	first->position = -1;
	first->next = NULL;
	first->prev = NULL;
}

void	test_print(t_input *first)
{
	t_input *cur;
	cur = first;
	 
	while(cur->next != first)
	{
		printf("node %d, content: %s:  cur %p, prev: %p, next: %p\n", cur->position, cur->content, &cur, cur->prev, cur->next);
		cur = cur->next;
	}
	printf("node %d, content: %s: cur %p, prev: %p, next: %p\n", cur->position, cur->content, &cur, cur->prev, cur->next);

}

int  parse_input(char *line, t_input *first)
{
	t_input	*cur;
	char 	**split;
	int 	pos = 0;

	split = ft_split(line, ' ');
	if (!split)
		return NULL; //handle later on
	//printf("test6\n");
	first = make_new_node(split[pos], pos);
	if (!first)
		return NULL; //handle later on
	
	pos++;
	cur = first;
	while(split[pos])
	{
		cur = add_new(split[pos], pos, cur);
		pos++;
		//protect
	}
	cur->next = first;
	test_print(first);
	free(split);
	return(1);
}

//check first thing in the list if it is executable

int main(void)
{
	char *line;
	t_input first;
	
	while (1)
	{
		line = readline("Minishell: ");
		if (strncmp(line, "exit", 5) == 0)
			break ;
		//printf("test7\n");
		init_input(&first);
		if (!parse_input(line, &first))
			continue ;		//error handling
		free(line);
	}
}