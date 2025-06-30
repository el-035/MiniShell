#include "minishell.h"

int	return_sig_flag(int sig)
{
	static int flag = 0;

	if (sig >= 0)
		flag = sig;
	return (flag);
}

int	parsing(t_input *first, t_data *data)	//return value?
{	
	if (assign_type(&first) != 0)
		return (free_list(first), 1);
/* 	printf("before exp:\n");
	test_print(first); */
	if (find_ev(first, data) != 0)
		return (free_list(first), 1);
/* 	printf("before second split:\n");
	test_print(first); */
	if (exp_split(first))
		return (free_list(first), 1);
	
	if (remove_quotes(first) != 0)
		return (free_list(first), 1);
	
/* test_print(first); */
	if (find_cmd(first) != 0)
		return (free_list(first), 1);
	
	
/* 	printf("after quotes:\n");
	test_print(first); */
	
	
	if (!parse_tokens(first, data))
		return (free_list(first), 1);
	free_list(first);
    //freegrepo
	//print_cmds(data);

	if (!create_pipes(data))
        return (1);

		
	
	if (!get_env_path(data, data->envp))
		return (1);
	
	if (!open_files(data))
		return_exit_code(1);
	
	if (!exec_proc(data, data->envp))
		return (1);
	return (0);
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

void	handler(int sig)
{
	if (sig == SIGINT)		//crtl C
	{
		//return_exit_code(130);		// this actually does not work :(
		return_sig_flag(1);
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

	var = extract_var(data->envp, ft_strdup("USER"));
	if (!var)
		return (NULL);
	tmp = ft_strjoin(var, ":~");
	free(var);
	if (!tmp)
		return (fail_mall(), NULL);
	var = extract_var(data->envp, ft_strdup("PWD"));
	if (!var)
		return (free(tmp),NULL);
	prompt = ft_strjoin(tmp, var);
	free(tmp); free(var);
	if (!prompt)
		return (NULL);
	//remove_useless_quotes(&prompt, return_final_len(prompt));
	return (prompt);
}

/* 	if (return_exit_code(-1) == 0 || return_sig_flag(-1) != 0)
	{
		//return_sig_flag(0);
		tmp = ft_strjoin("\001\033[1;32m\002", prompt);
	}
	else if (return_exit_code(-1) != 0)
		tmp = ft_strjoin("\001\033[1;31m\002", prompt); */

char	*prompt(t_data *data, char **envp)
{
	char *line;
	char *tmp;
	char *prompt;

	tmp = NULL;
	return_exit_code(0);
	return_sig_flag(0);
	if (!*envp)
		return (readline("\001\033[1;34m\002Minishell:\001\033[0m\002 "));
	prompt = prompt_join(data);
	if (!prompt)
		return (fail_mall(), NULL);
	if (return_exit_code(-1) == 0 )						//color is fucked up for ctrl c
		tmp = ft_strjoin("\001\033[1;32m\002", prompt);
	else if (return_exit_code(-1) != 0 || return_sig_flag(-1) == 1)
		tmp = ft_strjoin("\001\033[1;31m\002", prompt);
//	tmp = ft_strjoin("\001\033[1;34m\002", prompt); 
	free(prompt);
	if (!tmp)
		return (fail_mall(), NULL);
	prompt = ft_strjoin(tmp, "\001\033[0m\002 ");
	if (!prompt)
		return (fail_mall(), free(tmp), NULL);
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
	if (copy_envp(&data, envp) == -1)
		return (write(2, "Allocation failed\n", 18), 1);	//not sure here
	ft_memset(&sig, 0, sizeof(struct sigaction));
	sig.sa_handler = &handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;

	return_exit_code(0);
	while (1)
	{
		first = NULL;
		sigaction(SIGINT, &sig, NULL);
		sigaction(SIGQUIT, &sig, NULL);	//ignore

		line = prompt(&data, envp);
		if (!line)	//ctrl d
		{
			write (2, "exit\n", 5);
			break ;
		}
		if (!*line || !save_input(line, &first))
			continue ;		//error handling
	//	test_print(first);
		parsing(first, &data);	//here?
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

	//FREE_ALL func if cmd line fails, FREE_CMD if a single command fails


/* 
	export should redir output to file
*/


//EXPORT PATH="::" - have to check

/* 
Minishell: ./minishell
Minishell: exit | exit
Minishell: exit | exit
@TheTalkingFox ➜ /workspaces/MiniShell (sasha) $ 
exits when it shouldnt */

/* Minishell: echo hez > tewst
tewst: Permission denied
Minishell: echo $?
0
EC should be 1 */

//heredoc if ctrl + c EC 130 & does nothing

/* Minishell: cat << ok << ok <<
bash: syntax error near unexpected token
@TheTalkingFox ➜ /workspaces/MiniShell (sasha) $ cat << ok << ok <<
> sdfds
> dsfds
> ok
> ok
bash: syntax error near unexpected token `newline' */

/* HD leak:
cat << ok << oki 
> asdsad
> ok
> asdasd
> asdasdasasd
> asdzxczxc
> oki
asdasd
asdasdasasd
asdzxczxc
Minishell: ==46451== 
==46451== HEAP SUMMARY:
==46451==     in use at exit: 204,638 bytes in 217 blocks
==46451==   total heap usage: 639 allocs, 422 frees, 242,298 bytes allocated
==46451== 
==46451== 3 bytes in 1 blocks are definitely lost in loss record 1 of 60
==46451==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==46451==    by 0x10E96D: ft_calloc (in /workspaces/MiniShell/minishell)
==46451==    by 0x10E8CA: ft_strdup (in /workspaces/MiniShell/minishell)
==46451==    by 0x10CB6E: handle_heredoc (parse_input.c:90)
==46451==    by 0x10CD09: handle_token (parse_input.c:113)
==46451==    by 0x10CD6A: fill_cmd_data (parse_input.c:136)
==46451==    by 0x10CF3F: parse_tokens (parse_input.c:169)
==46451==    by 0x10974D: parsing (minishell.c:53)
==46451==    by 0x109B1B: main (minishell.c:184)
==46451== 
==46451== LEAK SUMMARY:
==46451==    definitely lost: 3 bytes in 1 blocks
==46451==    indirectly lost: 0 bytes in 0 blocks
==46451==      possibly lost: 0 bytes in 0 blocks
==46451==    still reachable: 0 bytes in 0 blocks
==46451==         suppressed: 204,635 bytes in 216 blocks */

/*  MiniShell git:(el) ✗ ./minishell 
efittant:~/home/efittant/Desktop/projects/CommonCore/mini/MiniShell echo $"$USER"
efittant
efittant:~/home/efittant/Desktop/projects/CommonCore/mini/MiniShell echo "$\"hello\""
$hello\
efittant:~/home/efittant/Desktop/projects/CommonCore/mini/MiniShell echo $\"hello\"
$\hello
efittant:~/home/efittant/Desktop/projects/CommonCore/mini/MiniShell echo $"hello"
hello */

/* efittant:~/home/efittant/Desktop/projects/CommonCore/mini/MiniShell cd ..
H==2025538== Conditional jump or move depends on uninitialised value(s)
==2025538==    at 0x402F03: exec_proc (exec.c:235)
==2025538==    by 0x401495: parsing (minishell.c:41)
==2025538==    by 0x4019BC: main (minishell.c:180)
==2025538==  */