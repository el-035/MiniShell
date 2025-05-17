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

int	parsing(t_input *first, t_data *data)	//return value?
{	
	if (assign_type(&first) != 0)
		return (return_exit_code(-1));
	/* if (!handle_heredoc(first, data))
			return (1); */
	
	
	// work on quotes

	if (find_ev(first, data) != 0)
		return (return_exit_code(-1));
	if (find_cmd(first) != 0)
		return (return_exit_code(-1));

	//expand $?
	find_exit(first, data);

	if (!parse_tokens(first, data))
		return (1);
    //freegrepo
	//print_cmds(data);
	if (!create_pipes(data))
        return (1);
	if (!get_env_path(data, data->envp))
		return (1);
	if (!open_files(data))
		return (1);
	if (!exec_proc(data, data->envp))
		return (1);
	
	return 0;
}



int	copy_envp(t_data *data, char **envp)
{
	int i;

	i = 0;
	if (!*envp)			//handle this
		return (printf("no env\n"), 1556);
	while (envp[i])
		i++;
	data->envp = (char **) ft_calloc(i + 1, sizeof(char *));
	if (!data->envp)
		return 1561;		//error
	i = 0;
	while (envp[i])
	{
		data->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	return 0;
}


/* char	*prompt(t_data *data)
{

} */


void	handler(int sig)
{
	if (sig == SIGINT)		//crtl C
	{
		return_exit_code(130);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)		//ctrl /
	{
	}
}

int	return_exit_code(int exit)
{
	//0			updates previous and resets exit to 0
	// > 0		update cur and return
	// -2		return cur without updating
	// -1		return old

	static int cur_exit = 0;
	static int old_exit = 0;

	if (exit > 0)
		cur_exit = exit;
	else if (exit == 0)
	{
		old_exit = cur_exit;
		cur_exit = exit;
	}
	else if (exit == -1)
		return (old_exit);
	else if (exit == -2)	//do we even ever need this??
		return (cur_exit);

	return (cur_exit);
}

int main(int argc, char **argv, char **envp)
{
	char 				*line;
	t_input 			*first;
	t_data				data;
	struct sigaction	sig;
	(void)argc;
	(void)argv;

 	first = NULL;
	ft_memset(&data, 0, sizeof(t_data));
	copy_envp(&data, envp);
	while (1)
	{
		sigaction(SIGINT, &sig, NULL);
		sigaction(SIGQUIT, &sig, NULL);
		return_exit_code(0);
		
		if (return_exit_code(-1) == 0)
			line = readline("\001\033[1;32m\002Minishell:\001\033[0m\002 ");	//double check
		else if (return_exit_code(-1) != 0)
			line = readline("\001\033[1;31m\002Minishell:\001\033[0m\002 ");	//double check
		if (!line)	//ctrl d
		{
			free_split(data.envp);
			free_all(&data);
			return (return_exit_code(1));	//	???
		}
		if (!*line || !save_input(line, &first))
			continue ;		//error handling
		parsing(first, &data);
 		printf("previous: %d\n", return_exit_code(-1));
		printf("current: %d\n", return_exit_code(-2));
		add_history(line);
		free(line);
		free_list(first);
		free_all(&data);
	}
	rl_clear_history();
	return (free_split(data.envp), return_exit_code(-1));
}
// ./minishell takes args. Shouldnt it?

//to run valgrind without readline leaks
//valgrind --leak-check=full --show-leak-kinds=all --suppressions=minishell.supp ./minishell