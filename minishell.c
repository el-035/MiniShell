#include "minishell.h"

int	parsing(t_input *first, t_data *data, char *line)	//return value?
{	

	if (assign_type(&first) != 0)
		return (free_list(first), 1);
	if (find_ev(first, data) != 0)
		return (free_list(first), 1);
	if (find_cmd(first) != 0)
		return (free_list(first), 1);
	if (!parse_tokens(first, data))
		return (free_list(first), 1);
	/* FREE INPUT */
	//extract_var(data->envp, "HOME");
	free_list(first);
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




int	return_exit_code(int exit)
{
	//0			updates previous and resets exit to 0
	// > 0		update cur and return it
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

/* int	return_sig_flag(int f)
{
	static int flag = 0;

	if (f == 1)
		flag = 1;
	else if (f == 0)
	{
		f = flag;
		flag = 0;	
		return (f);
	}
	return (flag);	
} */

void	handler(int sig)
{
	if (sig == SIGINT)		//crtl C
	{
		return_exit_code(130);		// :((
	//	return_sig_flag(1);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)		//ctrl /
	{
	}
}
char *prompt_join(t_data *data)
{
	char *prompt;
	char *tmp;
	char *var;
	char *col;

	var = extract_var(data->envp, ft_strdup("USER"));
	if (!var)
		return (write(2, "Allocation failed\n", 18), NULL);	//exit code for malloc failed???
	tmp = ft_strjoin(var, ":~");
	free(var);
	if (!tmp)
		return (write(2, "Allocation failed\n", 18), NULL);
	var = extract_var(data->envp, ft_strdup("PWD"));
	if (!var)
		return (write(2, "Allocation failed\n", 18), free(tmp), NULL);
	prompt = ft_strjoin(tmp, var);
	free(tmp); free(var);
	if (!prompt)
		return (write(2, "Allocation failed\n", 18), NULL);
	return (prompt);
}

char	*prompt(t_data *data)
{
	char *line;
	char *tmp;
	char *prompt;

	prompt = prompt_join(data);
	if (!prompt)
		return (NULL);
	if (return_exit_code(-1) == 0)
		tmp = ft_strjoin("\001\033[1;32m\002", prompt);
	else if (return_exit_code(-1) != 0)
		tmp = ft_strjoin("\001\033[1;31m\002", prompt);
	free(prompt);
	if (!tmp)
		return (write(2, "Allocation failed\n", 18), NULL);
	prompt =ft_strjoin(tmp, "\001\033[0m\002 ");
	if (!prompt)
		return (write(2, "Allocation failed\n", 18), free(tmp), NULL);
	line = readline(prompt);
	return (free(prompt), free(tmp), line);
}

int main(int argc, char **argv, char **envp)
{
	char 				*line;
	t_input 			*first;
	t_data				data;
	struct sigaction	sig;
	(void)argc;
	(void)argv;

	ft_memset(&data, 0, sizeof(t_data));
	data.fd1 = -1;
	data.fd2 = -1;
	copy_envp(&data, envp);

	ft_memset(&sig, 0, sizeof(struct sigaction));
	sig.sa_handler = &handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
	while (1)
	{
		first = NULL;
		return_exit_code(0);	//ctrlc works but when used the exit code is updated one loop later
		line = prompt(&data);
		if (!line)	//ctrl d
			break ;
		if (!*line || !save_input(line, &first)/*  || return_sig_flag(0) == 1 */)
			continue ;		//error handling
		parsing(first, &data, line);

		add_history(line);
		free(line);
		free_all(&data);
	}
	if (first)
		free_list(first);
	free_all(&data);
	rl_clear_history();
	return (free_split(data.envp), return_exit_code(-1));
}
//EXIT CODE FOR ALLOCATION FAILED?
//SHLVL not increased when running minishell inside of minishell
// ./minishell takes args. Shouldnt it?
//change bash to mnishell

//to run valgrind without readline leaks
//valgrind --leak-check=full --show-leak-kinds=all --suppressions=minishell.supp ./minishell


//free input after my part in parsing

/* Minishell: unset HOME
---- Before unset ----
---- After unset ----
==51055== Conditional jump or move depends on uninitialised value(s)
==51055==    at 0x10ACE3: exec_proc (exec.c:183)
==51055==    by 0x1097A0: parsing (minishell.c:80)
==51055==    by 0x109AE6: main (minishell.c:195)
==51055==  */

		// CAN BE ANY COMMANDS IN THE MIDDLE?
		//SHOULD WE HANDLE CHMOD

		//FOR saving lines:
/* 		while (data->a.top->index != min)
			if (pos <= find_stack_size(&data->a) / 2)
				rotate(&data->a, 1);
		else
			rev_rotate(&data->a, 1); */