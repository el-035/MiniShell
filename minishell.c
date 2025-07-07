#include "minishell.h"

int	parsing_execution(t_input *first, t_data *data)
{
	if (assign_type(&first) != 0)
		return (free_list(first), 1);
	if (find_ev(first, data) != 0)
		return (free_list(first), 1);
	if (remove_quotes(first) != 0)
		return (free_list(first), 1);
	if (find_cmd(first) != 0)
		return (free_list(first), 1);
	if (!parse_tokens(first, data))
		return (free_list(first), 1);
	free_list(first);
	if (!create_pipes(data))
		return (1);
	if (!get_env_path(data, data->envp))
		return (1);
	open_files(data);
	if (!exec_proc(data, data->envp))
		return (1);
	return (0);
}

int	main_loop(t_input *first, t_data *data, struct sigaction *sig, char **envp)
{
	char	*line;

	line = prompt(envp, data, sig);
	if (!line)
	{
		write(2, "exit\n", 5);
		return (1);
	}
	if (!*line)
	{
		data->ec_update_flag = 1;
		return (0);
	}
	if (!save_input(line, &first))
		return (0);
	parsing_execution(first, data); 
	(add_history(line), free(line),	free_all(data));
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_input				*first;
	t_data				data;
	struct sigaction	sig;

	(void)argc;
	(void)argv;
	ft_memset(&sig, 0, sizeof(struct sigaction));
	sig.sa_handler = &handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	if (init_stuff(&data, envp) == -1)
		return (1);
	while (1)
	{
		first = NULL;
		if (main_loop(first, &data, &sig, envp) == 1)
			break ;
	}
	if (first)
		free_list(first);
	free_all(&data);
	rl_clear_history();
	if (return_sig_flag(-1) != 0)
		return (free_split(data.envp), return_exit_code(130));
	return (free_split(data.envp), return_exit_code(-1));
}

// change bash to mnishell

// valgrind --leak-check=full --show-leak-kinds=all --suppressions=minishell.supp ./minishell

/* Minishell: unset HOME
---- Before unset ----
---- After unset ----
==51055== Conditional jump or move depends on uninitialised value(s)
==51055==    at 0x10ACE3: exec_proc (exec.c:183)
==51055==    by 0x1097A0: parsing (minishell.c:80)
==51055==    by 0x109AE6: main (minishell.c:195)
==51055==  */

// CAN BE ANY COMMANDS IN THE MIDDLE?
// SHOULD WE HANDLE CHMOD

// FOR saving lines:
/* 		while (data->a.top->index != min)
			if (pos <= find_stack_size(&data->a) / 2)
				rotate(&data->a, 1);
		else
			rev_rotate(&data->a, 1); */

// FREE_ALL func if cmd line fails, FREE_CMD if a single command fails

/*
	export should redir output to file
*/

// EXPORT PATH="::" - have to check

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

// heredoc if ctrl + c EC 130 & does nothing

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
==46451==    at 0x483B7F3: malloc (in
		/usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
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