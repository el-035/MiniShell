#include"minishell.h"


int compare_cmd(t_input *cur, char **commands)
{
	int i;

	i = 0;
	while (commands[i])
	{
		if (ft_strncmp(commands[i], cur->content, sizeof(cur->content)) == 0)
		{
			cur->is_builtin = 1;
			break ;
		}
		i++;
	}
	return 0;
}


int	is_built_in(t_input *first)
{
	char	commands = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	t_input	*cur;

	cur = first;
	while (cur)
	{
		if (cur->type == CMD)
			compare_cmd(cur, commands);
		if (cur->next)
			cur = cur->next;
		if (cur == first)
			break;
	}
}