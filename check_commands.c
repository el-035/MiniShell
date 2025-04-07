#include"minishell.h"

/* void print_paths(char **paths)
{
    int i = 0;
    while (paths[i])
    {
        printf("Path %d: %s\n", i, paths[i]);
        i++;
    }
} */
int search_path(t_input *cur, char **path)
{
	int i;
	char *cmd;
	char *full_p;

	cmd = ft_strjoin("/", cur->content);
	i = 0;
	while (path[i])
	{
		full_p = ft_strjoin(path[i], cmd);
		if (access(full_p, X_OK) == 0)		//??
		{
			cur->cmd_path = ft_strdup(full_p);
			return(free(cmd), free(full_p), free_split(path), 0);
		}
		free(full_p);
		i++;
	}
	return (free(cmd), free_split(path), write(2, " command not found\n", 19), 127);
}

int	get_cmd_path(t_input *cur)
{
	char	**path;

	path = ft_split(getenv("PATH"), ':');
	return (search_path(cur, path));
	return 0;
}

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
	int		exit;

	cur = first;
	exit = 0;
	while (cur)
	{
		if (cur->type == CMD)
		{
			compare_cmd(cur, commands);
			if (cur->is_builtin == 0)
			{
				exit = get_cmd_path(cur);
				if (exit != 0)
					return (exit);
			}
		}
		if (cur->next)
			cur = cur->next;
		if (cur == first)
			break;
	}
	return 0;
}
