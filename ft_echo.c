/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <efittant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:01:41 by efittant          #+#    #+#             */
/*   Updated: 2025/07/09 14:27:55 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_opt(char *opt)
{
	int	i;

	i = 1;
	if (opt[0] != '-')
		return (0);
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	nl;

	nl = 1;
	i = 1;
	signal(SIGPIPE, SIG_IGN);
	if (!cmd->args[i])
	{
		write(1, "\n", 1);
		return ;
	}
	else if (valid_opt(cmd->args[i]) == 1)
	{
		nl = 0;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], 1);
		if (cmd->args[i + 1])
			write(1, " ", 1);	
		i++;
	}
	if (nl == 1)
		write(1, "\n", 1);
}
