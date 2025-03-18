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
void	free_split(char **split)
{
	int	word;

	word = 0;
	while (split[word])
	{
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
		return 0; //handle later on
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
	//free(split); make function
	return(1);
}

//changed parse input with double pointer to first
//rewrote split

void	free_list(t_input *first)
{
	t_input	*cur;
	t_input	*tmp;

	if (!first) // Handle empty list
		return ;
	cur = first->next;
	while (cur != first)
	{
		tmp = cur;
		cur = cur->next;
		//free(tmp->content); // Free dynamically allocated content if needed
		free(tmp);
	}
	//free(first->content); // Free the content of the first node
	free(first);
}

int main(void)
{
	char *line;
	t_input *first;
	
	while (1)
	{
		line = readline("Minishell:~$ ");
		if (strncmp(line, "exit", 5) == 0)
			break ;
		if (!*line || !parse_input(line, &first))
			continue ;		//error handling
		assign_type(&first);
		//test_print(first);
		free(line);
	}
	free_list(first);
}