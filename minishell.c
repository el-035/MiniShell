/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <efittant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:57:54 by efittant          #+#    #+#             */
/*   Updated: 2025/07/07 22:13:14 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (!save_input(line, &first, 0))
		return (0);
	parsing_execution(first, data);
	(add_history(line), free(line), free_all(data));
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
