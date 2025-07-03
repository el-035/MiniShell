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
		if (cur->type == CMD)
		{
			/* remove_useless_quotes(&cur->content, return_final_len(cur->content)); */
			compare_cmd(cur, commands);
		}
		
		cur = cur->next;
		if (cur == first)
			break;
	}
	return 0;
}
