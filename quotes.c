#include "minishell.h"

int	check_quotes(char *content, int len)
{
	int	quote;
	int	i;

	i = 0;
	quote = 0;
	while (content[i] && i < len)
	{
		if (content[i] == '\'' && quote == 0)
			quote = 1;
		else if (content[i] == '\'' && quote == 1)
			quote = 0;
		else if (content[i] == '"' && quote == 0)
			quote = 2;
		else if (content[i] == '"' && quote == 2)
			quote = 0;
		i++;
	}
	return (quote);
}
/* int	check_quotes(char *content, int pos)
{
	int	i;
	int	in_single_quote;
	int	in_double_quote;

	if (!content || pos < 0)
		return (0);
	
	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	
	while (i < pos && content[i])
	{
		if (content[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (content[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		i++;
	}
	return (in_single_quote || in_double_quote);
} */
int	return_final_len(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' && check_quotes(str, i) != 1)
			i++;
		else if (str[i] == '\\' && check_quotes(str, i) == 2)
			i++;
		else if (str[i] == '\'' && check_quotes(str, i) != 2)
			i++;
		else
		{
			i++;
			j++;
		}
	}
	return (j);
}

int	remove_useless_quotes(char **content, int len)
{
	int		i;
	char	*final;

	i = 0;
	final = (char *)ft_calloc(len + 1, sizeof(char));
	if (!final)
		return (fail_mall(), 1);
	len = 0;
	while ((*content)[i])
	{
		if ((*content)[i] == '"' && check_quotes((*content), i) != 1)
			i++;
		else if ((*content)[i] == '\\' && check_quotes((*content), i) == 2)
			i++;
		else if ((*content)[i] == '\'' && check_quotes((*content), i) != 2)
			i++;
		else
			final[len++] = (*content)[i++];
	}
	free((*content));
	(*content) = ft_strdup(final);
	if (!(*content))
		return (free(final), fail_mall(), 1);
	return (free(final), 0);
}

/* int	remove_quotes(t_data *data)
{
	int i;
	int j;

	i = 0;

	while (i < data->cmd_count)
	{	

		if (data->cmds[i].args && data->cmds[i].args[0] && 
			ft_strncmp(data->cmds[i].args[0], "export", ft_strlen(data->cmds[i].args[0])) != 0)
		{
			j = 1;
			while(data->cmds[i].args[j])
			{
				if (ft_strchr(data->cmds[i].args[j], '\'') || ft_strchr(data->cmds[i].args[j], '"'))
				{
					if (remove_useless_quotes(&(data->cmds[i].args[j]), return_final_len(data->cmds[i].args[j])) != 0)
						return 1;
				}
				j++;
			}
		}
		if (data->cmds[i].in)
		{
			if (remove_useless_quotes(&(data->cmds[i].in), return_final_len(data->cmds[i].in)) != 0)
				return 1;
		}
		if (data->cmds[i].out)
		{
			if (remove_useless_quotes(&(data->cmds[i].out), return_final_len(data->cmds[i].out)) != 0)
				return 1;
		}
		i++;
	}
	return 0;
} */


int	remove_quotes(t_input *first, t_data *data)
{

	t_input	*cur;

	cur = first;
	while (cur)
	{
		if ((!cur->prev || cur->prev->type != HERE_DOC) // HD?
			&& ft_strnstr(cur->content, "$?", ft_strlen(cur->content)))
		{
			if (expand_exit(&cur, data) != 0)
				return (1);
		}
		if ((ft_strchr(cur->content, '\'') || ft_strchr(cur->content, '"'))
			&& cur->prev->type != HERE_DOC)
		{
			if (remove_useless_quotes(&(cur->content),
					return_final_len(cur->content)) != 0)
				return (1);
		}
		cur = cur->next;
		if (cur == first)
			break ;
	}
	return (0);
}