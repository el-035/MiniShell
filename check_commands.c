/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <efittant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:06:43 by efittant          #+#    #+#             */
/*   Updated: 2025/07/09 21:15:03 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**is_builtins(void)
{
	char	**commands;

	commands = ft_calloc(8, sizeof(char *));
	if (!commands)
		return (NULL);
	commands[0] = "echo";
	commands[1] = "cd";
	commands[2] = "pwd";
	commands[3] = "export";
	commands[4] = "unset";
	commands[5] = "env";
	commands[6] = "exit";
	commands[7] = NULL;
	return (commands);
}

int	compare_cmd(t_input *cur)
{
	int		i;
	char	**commands;

	commands = is_builtins();
	if (!commands)
		return (fail_mall(), -1);
	i = 0;
	while (i <= 6)
	{
		if (ft_strncmp(commands[i], cur->content, (ft_strlen(commands[i])
					+ 1)) == 0)
		{
			cur->is_builtin = 1;
			return (free(commands), 0);
		}
		i++;
	}
	return (free(commands), 0);
}

static int	ambiguous(t_input *first)
{
	t_input	*cur;

	cur = first;
	while (cur)
	{
		if (cur->type == CMD && ft_strncmp(cur->content, ".", 2) == 0)
		{
			if (cur->next == cur)
				return (write(2, "filename argument required\n", 27),
					return_exit_code(2), 1);
			else
			{
				cur->type = UNKNOWN;
				cur->next->type = CMD;
			}
		}
		if (cur->type == REDIR_OUT && cur->next->exp != INT_MIN)
			return (write(2, "ambiguous redirect\n", 19), return_exit_code(1),
				1);
		cur = cur->next;
		if (cur == first)
			break ;
	}
	return (0);
}

int	find_cmd(t_input *first)
{
	t_input	*cur;

	cur = first;
	while (cur)
	{
		if (cur->type == UNKNOWN)
			cur->type = ARG;
		if (/* cur->type == CMD &&  */cur->content[0] == '\0' && cur->exp != INT_MIN)
		{
			cur->type = UNKNOWN;
			if (cur->next != cur && cur->next->type == ARG)
				cur->next->type = CMD;
		}
		if (cur->type == CMD)
		{
			if (compare_cmd(cur) != 0)
				return (1);
		}
		cur = cur->next;
		if (cur == first)
			break ;
	}
	return (ambiguous(first));
}
