#include "minishell.h"

int	open_files(t_data *data)
{
	t_cmd	*cmd;
	int		i;
	int		j;
	int		total;

	i = -1;
	while (++i < data->cmd_count)
	{
		cmd = &data->cmds[i];
		if (!cmd->args || !cmd->args[0])
			add_skip_flag(cmd, i, data->cmd_count, 2);
		j = -1;
		total = cmd->in_redirs + cmd->out_redirs;
		while (cmd->redir_order && ++j < total)
		{
			if (cmd->redir_order[j] == 1)
				if (!check_in(data, i))
					break ;
			if (cmd->redir_order[j] == 2)
				if (!check_out(data, i))
					break ;
		}
	}
	return (1);
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

int  count_redirs(t_cmd *cmd, t_input *input, t_input *start)
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

void handle_redirs(t_cmd *cmd, t_input **cur)
{
	int	redir_ind;

	redir_ind = cmd->in_index + cmd->out_index;
	if ((*cur)->type == REDIR_IN && (*cur)->next)
	{
		if (cmd->in && cmd->in_index < cmd->in_redirs)
		{
			cmd->in[cmd->in_index++] = ft_strdup((*cur)->next->content);
			cmd->redir_order[redir_ind] = 1;
		}
	}
	else if (((*cur)->type == REDIR_OUT || (*cur)->type == REDIR_APPEND)
		&& (*cur)->next)
	{
		if (cmd->out && cmd->out_index < cmd->out_redirs)	
		{
			cmd->out[cmd->out_index++] = ft_strdup((*cur)->next->content);
			if ((*cur)->type == REDIR_APPEND)
				cmd->append = 1;
			else
				cmd->append = 0;
			cmd->redir_order[redir_ind] = 2;
		}
	}
	*cur = (*cur)->next;
}
