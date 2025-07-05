/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <apchelni@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 00:54:42 by apchelni          #+#    #+#             */
/*   Updated: 2025/04/18 17:48:36 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		exit(SIGINT + 128);
	}
	if (sig == SIGQUIT)
		exit(SIGQUIT + 128);
}

void	hd_handler(int sig)
{
	if (sig == SIGINT)
	{
		return_exit_code(SIGINT + 128);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		return_sig_flag(2);
		rl_on_new_line();
		rl_replace_line("", 0);
		return ;
	}
	if (sig == SIGQUIT)
	{
		return_sig_flag(3);
	}
}
