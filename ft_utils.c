/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <efittant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 00:54:42 by apchelni          #+#    #+#             */
/*   Updated: 2025/07/07 19:57:34 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int	count_word(char *content)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	if (!content)
		return (0);
	while (content[i])
	{
		while (content[i] && is_space(content[i]) == 1)
			i++;
		if (content[i] && is_space(content[i]) == 0)
		{
			wc++;
			while (content[i] && is_space(content[i]) == 0)
				i++;
		}
	}
	return (wc);
}

int	get_env_path(t_data *data, char **envp)
{
	int	cmp;
	int	i;

	i = -1;
	while (envp[++i])
	{
		cmp = ft_strncmp(envp[i], "PATH=", 5);
		if (cmp == 0)
		{
			data->env_path = ft_split(envp[i] + 5, ':');
			break ;
		}
	}
	return (1);
}

void	count_cmds(t_input *tokens, t_data *data)
{
	t_input	*cur;

	cur = tokens;
	data->cmd_count = 1;
	while (cur)
	{
		if (cur->type == PIPE)
			data->cmd_count++;
		cur = cur->next;
		if (cur == tokens)
			break ;
	}
}
