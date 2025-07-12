/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <efittant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:34:08 by efittant          #+#    #+#             */
/*   Updated: 2025/07/12 22:30:50 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_stuff(t_data *data, char **envp)
{
	ft_memset(data, 0, sizeof(t_data));
	data->fd1 = -1;
	data->fd2 = -1;
	data->pipes[0][0] = -1;
	data->pipes[0][1] = -1;
	data->pipes[1][0] = -1;
	data->pipes[1][1] = -1;
	if (copy_envp(data, envp) == -1)
		return (fail_mall(), -1);
	return_exit_code(0);
	return (0);
}

char	*prompt(char **envp, t_data *data, struct sigaction *sig)
{
	char	*line;
	char	*prompt;

	prompt = NULL;
	line = NULL;
	sigaction(SIGINT, sig, NULL);
	signal(SIGQUIT, SIG_IGN);
	if (data->ec_update_flag == 0)
	{
		data->prev_ec_code = return_exit_code(-2);
		return_exit_code(0);
	}
	data->ec_update_flag = 0;
	return_sig_flag(0);
	if (!*envp)
		prompt = "\001\033[1;34m\002Minishell: \001\033[0m\002";
	else if (data->prev_ec_code == 0)
		prompt = "\001\033[1;32m\002Minishell: \001\033[0m\002";
	else if (data->prev_ec_code != 0)
		prompt = "\001\033[1;31m\002Minishell: \001\033[0m\002";
	line = readline(prompt);
	return (line);
}

void	line_helper(t_data *data, char **args)
{
	handle_error(args[0], 2);
	free_split(data->envp);
	free_all(data);
}
