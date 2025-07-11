/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <efittant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:02:18 by efittant          #+#    #+#             */
/*   Updated: 2025/07/11 17:53:18 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **env)
{
	int	i;

	i = -1;
	signal(SIGPIPE, SIG_IGN);
	while (env[++i])
	{
		if ((ft_strchr(env[i], '=')))
		{
			ft_putstr_fd(env[i], 1);
			write(1, "\n", 1);
		}
	}
}
