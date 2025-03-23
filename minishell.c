#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void init_input(t_input *first)
{

	first->content = NULL;
	first->type = UNKNOWN;	
	first->position = -1;
	first->next = NULL;
	first->prev = NULL;

}

void free_split(char **split)
{
	int	word;

	word = 0;
	if (!split)
		return ;
	while (split[word])
	{
		if (split[word])	
			free(split[word]);
		word++;
	}
	free(split);
	return ;
}

int  parse_input(char *line, t_input **first)
{
	t_input	*cur;
	char 	**split;
	int 	pos = 0;

	split = mini_split(line);
	if (!split)
		return 0;
	*first = make_new_node(split[pos], pos);
	if (!*first)
		return (free_split(split), 0);
	pos++;
	cur = *first;
	while(split[pos])
	{	
		cur = add_new(split[pos], pos, cur);
		if (!cur)
			return 0;
		pos++;
	}
	cur->next = *first;
	free_split(split);
	return(1);
}

void	free_list(t_input *first)
{
	t_input	*cur;
	t_input	*tmp;

	if (!first)
		return ;
	cur = first;
	tmp = NULL;
	while (cur)
	{
		tmp = cur->next;
		if (cur->content)
			free(cur->content);
		free(cur);
		if (tmp == first)
			break ;
		cur = tmp;
	}
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
		if (!*line || !parse_input(line, &first))
			continue ;		//error handling
		assign_type(&first);
		test_print(first);
		free(line);
		free_list(first);
	}
	//rl_clear_history();	//
}