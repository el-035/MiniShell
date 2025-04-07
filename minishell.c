#include "minishell.h"

void init_input(t_input *first)
{
	first->content = NULL;
	first->type = UNKNOWN;	
	first->position = -1;
	first->next = NULL;
	first->prev = NULL;
	first->is_builtin = -1;
	first->cmd_path = NULL;
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
	// here doc
	// work on quotes
	find_ev(first);
	exit = find_cmd(first);
	if (exit != 0)
		return (exit);
	return 0;	//
}
/* void	handler(int sig)
{
	if (sig == SIGINT)
	{

	}
} */

int main(void)
{
	char 				*line;
	t_input 			*first;
	//struct sigaction	sig;
	int					exit;
	
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
		/* sig.sa_handler = handler;
		sigaction(SIGINT, &sig, NULL);
		sigaction(SIGQUIT, &sig, NULL); */
		//ctrl d
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
