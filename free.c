/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <apchelni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:25:19 by efittant          #+#    #+#             */
/*   Updated: 2025/07/12 03:44:05 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fail_mall(void)
{
	write(2, "Allocation failed\n", 18);
	return_exit_code(1);
}

void	free_split(char **split)
{
	int	word;

	word = 0;
	if (!split)
		return ;
	while (split[word])
	{
		if (split[word])
			free(split[word]);
		word++;
	}
	free(split);
	split = NULL;
	return ;
}

void	free_list(t_input *first)
{
	t_input	*cur;
	t_input	*tmp;

	if (!first)
		return ;
	cur = first;
	tmp = NULL;
	while (cur)
	{
		tmp = cur->next;
		if (cur->content)
			free(cur->content);
		if (cur)
			free(cur);
		if (tmp == first)
			break ;
		cur = tmp;
	}
	first = NULL;
}

void	close_child(t_data *data)
{
	free_all(data);
	free_split(data->envp);
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	rl_clear_history();
}
