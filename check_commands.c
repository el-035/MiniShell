#include"minishell.h"

int compare_cmd(t_input *cur, char **commands)
{
	int i;

	i = 0;
	while (i <= 6)
	{
		if (ft_strncmp(commands[i], cur->content, (strlen(commands[i]) + 1)) == 0)
		{
			cur->is_builtin = 1;
			return 0;
		}
		i++;
	}
	cur->is_builtin = 0;
	return 0;
}

int	find_cmd(t_input *first)
{
	char	*commands[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	t_input	*cur;

	cur = first;
	while (cur)
	{	
		if (cur->type == UNKNOWN)
			cur->type = ARG;
		if (cur->type == CMD && cur->content[0] == '\0' && cur->exp != INT_MIN)
		{
			cur->type = UNKNOWN;//remove useleess node??
			if (cur->next != cur)
				cur->next->type = CMD;		
		}
		if (cur->type == CMD)
			compare_cmd(cur, commands);
		
		cur = cur->next;
		if (cur == first)
			break;
	}
	return 0;
}
