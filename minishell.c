#include "minishell.h"

void init_input(t_input *first)
{
	first->content = NULL;
	first->type = UNKNOWN;	
	first->position = -1;
	first->next = NULL;
	first->prev = NULL;
}

int  save_input(char *line, t_input **first)
{
	t_input	*cur;
	char 	**split;
	int 	pos = 0;
	
	split = mini_split(line);
	if (!split)
		return 0;
	*first = make_new_node(split[pos], pos);
	if (!*first)
		return (free_split(split), printf("Error\nAllocation failed\n"), 0);
	pos++;
	cur = *first;
	while(split[pos])
	{	
		cur = add_new(split[pos], pos, cur);
		if (!cur)
			return (free_split(split), free_list(*first), printf("Error\nAllocation failed\n"), 0);
		pos++;
	}
	cur->next = *first;
	free_split(split);
	return(1);
}

int main(void)
{
	char *line;
	t_input *first;
	
	first = NULL;
	while (1)
	{
		line = readline("Minishell:~$ ");
		if (strncmp(line, "exit", 5) == 0)	//needs to be a command
			return (free(line), 1);
		if (!*line || !save_input(line, &first))
			continue ;		//error handling
		assign_type(&first);
		//test_print(first);
		free(line);
		free_list(first);
	}
	//rl_clear_history();	//
}