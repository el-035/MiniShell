/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <efittant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 00:54:42 by apchelni          #+#    #+#             */
/*   Updated: 2025/07/11 18:38:12 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(char *str, int error_code)
{
	if (error_code == 0)
	{
		write(2, str, ft_strlen(str));
		write(2, ": No such file or directory\n", 28);
	}
	else if (error_code == 1)
	{
		write(2, str, ft_strlen(str));
		write(2, ": Permission denied\n", 20);
	}
	else if (error_code == 2)
	{
		write(2, str, ft_strlen(str));
		write(2, ": command not found\n", 20);
		rl_clear_history();
	}
	else if (error_code == 3)
	{
		write(2, str, ft_strlen(str));
		write(2, ": Is a directory\n", 17);
	}
	else if (error_code == 4)
	{
		write(2, str, ft_strlen(str));
		perror(" ");
	}
}
