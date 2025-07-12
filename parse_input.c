/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <efittant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 00:54:42 by apchelni          #+#    #+#             */
/*   Updated: 2025/07/12 23:29:06 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(t_input *cur)
{
	int		argc;
	t_input	*tmp;

	argc = 0;
	tmp = cur;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CMD || tmp->type == ARG)
			argc++;
		tmp = tmp->next;
		if (tmp == cur)
			break ;
	}
	return (argc);
}

static int	handle_token(t_cmd *cmd, t_input **cur, int *j, t_data *data)
{
	if (((*cur)->type == CMD || (*cur)->type == ARG) && (!(*cur)->prev || \
			((*cur)->prev->type != REDIR_IN && (*cur)->prev->type != REDIR_OUT \
			&& (*cur)->prev->type != REDIR_APPEND)))
	{
		cmd->args[(*j)++] = ft_strdup((*cur)->content);
		if (!cmd->args[(*j) - 1])
			return (fail_mall(), 0);
		if ((*cur)->type == CMD)
			cmd->is_builtin = (*cur)->is_builtin;
	}
	else if (((*cur)->type == REDIR_IN || (*cur)->type == REDIR_OUT
			|| (*cur)->type == REDIR_APPEND) && (*cur)->next)
	{
		if (!handle_redirs(cmd, cur))
			return (0);
	}
	else if ((*cur)->type == HERE_DOC)
		if (!handle_heredoc(cmd, cur, data->envp))
			return (0);
	return (1);
}

static int	fill_cmd_data(t_cmd *cmd, t_input **cur, t_input *t, t_data *data)
{
	int	j;

	j = 0;
	while (*cur && (*cur)->type != PIPE)
	{
		if (!handle_token(cmd, cur, &j, data))
			return (0);
		*cur = (*cur)->next;
		if (*cur == t)
			break ;
	}
	cmd->args[j] = NULL;
	if (*cur && (*cur)->type == PIPE)
	{
		*cur = (*cur)->next;
		if (*cur == t)
			*cur = NULL;
	}
	return (1);
}

int	parse_tokens(t_input *tokens, t_data *data)
{
	int		i;
	t_input	*cur;
	t_cmd	*cmd;

	cur = tokens;
	count_cmds(tokens, data);
	data->cmds = ft_calloc(data->cmd_count, sizeof(t_cmd));
	if (!data->cmds)
		return (0);
	i = -1;
	while (cur && ++i < data->cmd_count)
	{
		cmd = &data->cmds[i];
		ft_memset(cmd, 0, sizeof(t_cmd));
		cmd->args = ft_calloc(count_args(cur) + 1, sizeof(char *));
		if (!cmd->args)
			return (0);
		if (!count_redirs(cmd, cur, tokens))
			return (0);
		if (!fill_cmd_data(cmd, &cur, tokens, data))
			return (0);
	}
	return (1);
}
