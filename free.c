#include "minishell.h"

//void	free_everything();

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
	split = NULL;
	return ;
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
		
		if (cur->is_builtin == 0 && cur->cmd_path)
			free(cur->cmd_path);
		if (cur)
			free(cur);
		if (tmp == first)
			break ;
		cur = tmp;
	}
	first = NULL;
}
