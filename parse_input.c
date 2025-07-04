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

static void	handle_token(t_cmd *cmd, t_input **cur, int *j, t_data *data)
{
	if (((*cur)->type == CMD || (*cur)->type == ARG) && (!(*cur)->prev
			|| ((*cur)->prev->type != REDIR_IN
				&& (*cur)->prev->type != REDIR_OUT
				&& (*cur)->prev->type != REDIR_APPEND)))
	{
		//LEAK HERE
		cmd->args[(*j)++] = ft_strdup((*cur)->content);
		if ((*cur)->type == CMD)
			cmd->is_builtin = (*cur)->is_builtin;
	}
	else if (((*cur)->type == REDIR_IN || (*cur)->type == REDIR_OUT
			|| (*cur)->type == REDIR_APPEND) && (*cur)->next)
		handle_redirs(cmd, cur);
	else if ((*cur)->type == HERE_DOC)
		if (!handle_heredoc(cmd, cur, data->envp))
	//CHANGE THIS SHIIIT
			printf("Oopsy\n");
}

void	fill_cmd_data(t_cmd *cmd, t_input **cur, t_input *tokens, t_data *data)
{
	int	j;

	j = 0;
	while (*cur && (*cur)->type != PIPE)
	{
		handle_token(cmd, cur, &j, data);
		*cur = (*cur)->next;
		if (*cur == tokens)
			break ;
	}
	cmd->args[j] = NULL;
	if (*cur && (*cur)->type == PIPE)
	{
		*cur = (*cur)->next;
		if (*cur == tokens)
			*cur = NULL;
	}
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
		fill_cmd_data(cmd, &cur, tokens, data);
	}
	return (1);
}
