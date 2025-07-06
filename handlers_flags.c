/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <apchelni@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 00:54:42 by apchelni          #+#    #+#             */
/*   Updated: 2025/04/18 17:48:36 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		return_sig_flag(1);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

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
}

int	return_exit_code(int exit)
{
	static int	cur_exit = 0;
	static int	old_exit = 0;

	if (exit > 0)
		cur_exit = exit;
	else if (exit == 0)
	{
		old_exit = cur_exit;
		cur_exit = exit;
	}
	else if (exit == -1)
		return (old_exit);
	else if (exit == -2)
		return (cur_exit);
	return (cur_exit);
}

int	return_sig_flag(int sig)
{
	static int	flag = 0;

	if (sig >= 0)
		flag = sig;
	return (flag);
}
