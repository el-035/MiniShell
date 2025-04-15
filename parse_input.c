#include "minishell.h"

static int	count_cmds(t_input *tokens, t_data *data)
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
	data->cmds = ft_calloc(data->cmd_count, sizeof(t_cmd));
	if (!data->cmds)
		return (perror("Malloc: "), free_all(data), 0);
	return (1);
}

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

/* int exec_parse(t_input *cur, t_cmd *cmd)
{
    int j;

    j = 0;
    while (cur && cur->type != PIPE)
    {
        if ((cur->type == CMD || cur->type == ARG) && (!cur->prev || (cur->prev->type != REDIR_IN
                    && cur->prev->type != REDIR_OUT
                    && cur->prev->type != REDIR_APPEND)))
            cmd->args[j++] = ft_strdup(cur->content);
        else if (cur->type == REDIR_IN && cur->next)
        {
            cmd->in = ft_strdup(cur->next->content);
            cur = cur->next;
        }
        else if ((cur->type == REDIR_OUT || cur->type == REDIR_APPEND)
                 && cur->next)
        {
            cmd->out = ft_strdup(cur->next->content);
            cmd->append = (cur->type == REDIR_APPEND);
            cur = cur->next;
        }
        cur = cur->next;
    }
    cmd->args[j] = NULL;
    return 1;
} */


int	parse_tokens(t_input *tokens, t_data *data)
{
	int		i;
	int		j;
	t_input	*cur;
	t_cmd	*cmd;

	i = -1;
	cur = tokens;
	printf("%d\n", count_cmds(tokens, data));
	if (!count_cmds(tokens, data))
		return (0);
	while (cur && ++i < data->cmd_count)
	{
		cmd = &data->cmds[i];
		cmd->args = ft_calloc(count_args(cur) + 1, sizeof(char *));
		if (!cmd->args)
			return (perror("Malloc: "), free_all(data), 0);
		j = 0;
		while (cur && cur->type != PIPE)
		{
			if ((cur->type == CMD || cur->type == ARG) && (!cur->prev
					|| (cur->prev->type != REDIR_IN
						&& cur->prev->type != REDIR_OUT
						&& cur->prev->type != REDIR_APPEND)))
				cmd->args[j++] = ft_strdup(cur->content);
			else if (cur->type == REDIR_IN && cur->next)
			{
				cmd->in = ft_strdup(cur->next->content);
				cur = cur->next;
			}
			else if ((cur->type == REDIR_OUT || cur->type == REDIR_APPEND)
				&& cur->next)
			{
				cmd->out = ft_strdup(cur->next->content);
				cmd->append = (cur->type == REDIR_APPEND);
				cur = cur->next;
			}
			cur = cur->next;
			if (cur == tokens)
				break ;
		}
		cmd->args[j] = NULL;
		if (cur && cur->type == PIPE)
		{
			cur = cur->next;
			if (cur == tokens)
				break ;
		}
	}
	return (1);
}
