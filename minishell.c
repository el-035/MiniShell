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
	// here doc
	// work on quotes
	if (find_ev(first) != 0)
		return (return_exit_code(-1));
	if (find_cmd(first, data) != 0)
		return (return_exit_code(-1));
	return 0;	//
}


int	return_exit_code(int exit)	//pass negative to just read the current exit code, any other value will update it
{
	static int f_exit = 0;

	if (exit >= 0)
		f_exit = exit;
	return (f_exit);
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
/* int		return_sig_flag(int flag)
{
	static int	t_flag = 0;

	if (flag != -1)
		t_flag = flag;
	return (t_flag);
} */

/* void	handler(int sig)
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
} */

int main(int argc, char **argv, char **envp)
{
	char 				*line;
	t_input 			*first;
	t_data				*data;
	//struct sigaction	sig;
	(void)argc;
	(void)argv;

	data = malloc (sizeof(t_data));
	if (!data)
		return (326482973);		//error
	ft_memset(data, 0, sizeof(t_data));
	first = NULL;
	copy_envp(data, envp);
	while (1)
	{
/* 		sig.sa_handler = handler;
		sigemptyset(&sig.sa_mask);
		sigaction(SIGINT, &sig, NULL);
		sigaction(SIGQUIT, &sig, NULL);  */
		if (return_exit_code(-1) == 0)
			line = readline("\001\033[1;32m\002Minishell:\001\033[0m\002 ");	//double check
		else if (return_exit_code(-1) != 0)
			line = readline("\001\033[1;31m\002Minishell:\001\033[0m\002 ");	//double check
		
		if (!*line || !save_input(line, &first))
			continue ;		//error handling
		return_exit_code(0);
		parsing(first, data);
		//test_print(first);
		printf("%d\n", return_exit_code(-1));
		add_history(line);
		free(line);
		free_list(first);
	}
	rl_clear_history();
	return (free_split(data->envp), return_exit_code(-1));
}

