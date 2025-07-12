/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <efittant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 23:32:41 by efittant          #+#    #+#             */
/*   Updated: 2025/07/09 18:28:44 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	cwd[1024];

	signal(SIGPIPE, SIG_IGN);
	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putstr_fd(cwd, 1);
		write(1, "\n", 1);
	}
	else
		perror("pwd");
}
