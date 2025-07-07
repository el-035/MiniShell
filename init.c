/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <efittant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:34:08 by efittant          #+#    #+#             */
/*   Updated: 2025/07/07 19:35:32 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_stuff(t_data *data, char **envp)
{
	ft_memset(data, 0, sizeof(t_data));
	data->fd1 = -1;
	data->fd2 = -1;
	if (copy_envp(data, envp) == -1)
		return (fail_mall(), -1);
	return_exit_code(0);
	return (0);
}

char	*prompt(char **envp, t_data *data, struct sigaction *sig)
{
	char	*line;
	char	*prompt;

	sigaction(SIGINT, sig, NULL);
	signal(SIGQUIT, SIG_IGN);
	if (data->ec_update_flag == 0)
		return_exit_code(0);
	data->ec_update_flag = 0;
	return_sig_flag(0);
	if (!*envp)
		prompt = "\001\033[1;34m\002Minishell: \001\033[0m\002";
	else if (return_exit_code(-1) == 0)
		prompt = "\001\033[1;32m\002Minishell: \001\033[0m\002";
	else if (return_exit_code(-1) != 0 || return_sig_flag(-1) == 1)
		prompt = "\001\033[1;31m\002Minishell: \001\033[0m\002";
	line = readline(prompt);
	return (line);
}
