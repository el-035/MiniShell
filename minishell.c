#include "minishell.h"

void init_input(t_input *first)
{
	first->content = NULL;
	first->type = UNKNOWN;	
	first->position = -1;
	first->next = NULL;
	first->prev = NULL;
	first->is_builtin = 0;
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
	if (pos > 1)
	{
		cur->next = *first;
		(*first)->prev = cur;
	}
	free_split(split);
	return(1);
}

int	parsing(t_input *first)	//return value?
{
	int exit;
	
	exit = assign_type(&first);
	if (exit != 0)
		return (exit);
	find_ev(first);
	is_built_in(first);
	return 0;	//
}

int main(void)
{
	char *line;
	t_input *first;
	int	exit;
	
	exit = 0;
	first = NULL;
	while (1)
	{
		line = readline("\001\033[1;32m\002Minishell:\001\033[0m\002 ");	//double check
		if (strncmp(line, "exit", 5) == 0)	//needs to be a command
			return (free(line), 1);
		if (!*line || !save_input(line, &first))
			continue ;		//error handling
		exit = parsing(first);
		//printf("%d", exit);
		test_print(first);
		add_history(line);
		free(line);
		free_list(first);
		if (exit != 0)
			break ;
	}
	rl_clear_history();
	return (exit);
}