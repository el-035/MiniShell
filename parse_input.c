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

static void handle_redirs(t_cmd *cmd, t_input **cur)
{
	if ((*cur)->type == REDIR_IN && (*cur)->next)
	{
		cmd->in = ft_strdup((*cur)->next->content);
		*cur = (*cur)->next;
	}
	else if (((*cur)->type == REDIR_OUT || (*cur)->type == REDIR_APPEND)
		&& (*cur)->next)
	{
		cmd->out = ft_strdup((*cur)->next->content);
		cmd->append = ((*cur)->type == REDIR_APPEND);
		*cur = (*cur)->next;
	}
}

int	create_heredoc(t_cmd *cmd, char **envp)
{
	char *line;
	int count;
	char **new_lines;
	int	i;

	count = 0;
	while (1)
	{
		line = readline("> ");
		//FOR THE EOF + ctrl D (EOF char)
		/* if (*line == 26)
			return (printf("hey\n"), 0); */
		if (!line || ft_strcmp(line, cmd->limiter) == 0)
			break ;
		expand_var(&line, envp);
		new_lines = ft_calloc(sizeof(char *), count + 2);
		if (!new_lines)
			return (perror("Malloc: "), 0);
		i = -1;
		while (++i < count)
			new_lines[i] = cmd->hd_content[i];
		new_lines[count] = line;
		new_lines[count + 1] = NULL;
		free(cmd->hd_content);
		cmd->hd_content = new_lines;
		count++;		
	}
	free(line);
	return (1);
} 

int	handle_heredoc(t_cmd *cmd, t_input **cur, char **envp)
{
	if (!(*cur)->next)
		return (0);
	cmd->limiter = ft_strdup((*cur)->next->content);
	if (!create_heredoc(cmd, envp))
		return (0);
	cmd->is_hd = 1;
	*cur = (*cur)->next;
	return (1);
}

static void	handle_token(t_cmd *cmd, t_input **cur, int *j, t_data *data)
{
	if (((*cur)->type == CMD || (*cur)->type == ARG) && (!(*cur)->prev
			|| ((*cur)->prev->type != REDIR_IN
				&& (*cur)->prev->type != REDIR_OUT
				&& (*cur)->prev->type != REDIR_APPEND)))
	{
		cmd->args[(*j)++] = ft_strdup((*cur)->content);
		if ((*cur)->type == CMD)
			cmd->is_builtin = (*cur)->is_builtin;
	}
	else if (((*cur)->type == REDIR_IN || (*cur)->type == REDIR_OUT
			|| (*cur)->type == REDIR_APPEND) && (*cur)->next)
		handle_redirs(cmd, cur);
	else if ((*cur)->type == HERE_DOC)
		if (!handle_heredoc(cmd, cur, data->envp))
			printf("Oopsy\n");
	 
// END of FILE handle as character - exits HD but not bash:
/* apchelni@c2r5p12:~$ cat << EOF
> 
bash: warning: here-document at line 1 delimited by end-of-file (wanted `EOF')
apchelni@c2r5p12:~$ man ascii
 */
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
		return (perror("Malloc: "), free_all(data), 0);
	i = -1;
	while (cur && ++i < data->cmd_count)
	{
		cmd = &data->cmds[i];
		ft_memset(cmd, 0, sizeof(t_cmd));
		cmd->args = ft_calloc(count_args(cur) + 1, sizeof(char *));
		if (!cmd->args)
			return (perror("Malloc: "), 0);
		fill_cmd_data(cmd, &cur, tokens, data);
	}
//	print_cmds(data);
	return (1);
}
