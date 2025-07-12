/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <apchelni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 00:54:42 by apchelni          #+#    #+#             */
/*   Updated: 2025/07/12 03:25:27 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_files(t_data *data)
{
	t_cmd	*cmd;
	int		j;
	int		total;
	int		i;

	i = -1;
	while (++i < data->cmd_count)
	{
		cmd = &data->cmds[i];
		if (!cmd->args || !cmd->args[0])
			add_skip_flag(cmd);
		j = -1;
		total = cmd->in_redirs + cmd->out_redirs;
		while (cmd->redir_order && ++j < total)
		{
			if ((cmd->redir_order[j] == 1 && !check_in(data, i))
				|| (cmd->redir_order[j] == 2 && !check_out(data, i)))
			{
				cmd->redir_ec_flag = 1;
				break ;
			}
		}
	}
	return (return_exit_code(cmd->redir_ec_flag), 1);
}

int	alloc_redirs(t_cmd *cmd)
{
	if (cmd->in_redirs > 0)
	{
		cmd->in = ft_calloc(cmd->in_redirs + 1, sizeof(char *));
		if (!cmd->in)
			return (0);
	}
	if (cmd->out_redirs > 0)
	{
		cmd->out = ft_calloc(cmd->out_redirs + 1, sizeof(char *));
		if (!cmd->out)
			return (0);
	}
	cmd->redir_order = ft_calloc(cmd->in_redirs + cmd->out_redirs, sizeof(int));
	if (!cmd->redir_order)
		return (0);
	return (1);
}

int	count_redirs(t_cmd *cmd, t_input *input, t_input *start)
{
	t_input	*cur;

	cur = input;
	while (cur && cur->type != PIPE)
	{
		if (cur->type == REDIR_IN)
			cmd->in_redirs++;
		else if (cur->type == REDIR_APPEND || cur->type == REDIR_OUT)
			cmd->out_redirs++;
		cur = cur->next;
		if (cur == start)
			break ;
	}
	if (!alloc_redirs(cmd))
		return (fail_mall(), 0);
	return (1);
}

static int	check_red_file(t_cmd *cmd, t_input **cur, int redir_ind, int mode)
{
	char	*file;

	file = ft_strdup((*cur)->next->content);
	if (file)
	{
		if (mode == 1)
		{
			cmd->in[cmd->in_index++] = file;
			cmd->redir_order[redir_ind] = 1;
			return (1);
		}
		else if (mode == 2)
		{
			cmd->out[cmd->out_index++] = file;
			if ((*cur)->type == REDIR_APPEND)
				cmd->append = 1;
			else
				cmd->append = 0;
			cmd->redir_order[redir_ind] = 2;
			return (1);
		}
	}
	return (0);
}

int	handle_redirs(t_cmd *cmd, t_input **cur)
{
	int	redir_ind;

	redir_ind = cmd->in_index + cmd->out_index;
	if ((*cur)->type == REDIR_IN && (*cur)->next)
	{
		if (cmd->in && cmd->in_index < cmd->in_redirs)
			if (!check_red_file(cmd, cur, redir_ind, 1))
				return (0);
	}
	else if (((*cur)->type == REDIR_OUT || (*cur)->type == REDIR_APPEND)
		&& (*cur)->next)
	{
		if (cmd->out && cmd->out_index < cmd->out_redirs)
			if (!check_red_file(cmd, cur, redir_ind, 2))
				return (0);
	}
	*cur = (*cur)->next;
	return (1);
}
