#include "minishell.h"

int	check_quotes(char *content, int len)
{
	int	quote;
	int	i;

	i = 0;
	quote = 0;
	while (content[i] && i <= len)
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

int	return_final_len(char *str, int exp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' && check_quotes(str, i) != 1 && exp != 2)
			i++;
		else if (str[i] == '\\' && check_quotes(str, i) == 2 && exp != 2)
			i++;
		else if (str[i] == '\'' && check_quotes(str, i) != 2 && exp != 2)
			i++;
		else
		{
			i++;
			j++;
		}
	}
	return (j);
}

int	remove_useless_quotes(char **content, int len, int exp)
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
/* 		if (((*content)[i] == '"' || (*content)[i] == '\'') && exp == 1)
			i++; */
		/* else */ if ((*content)[i] == '"' && check_quotes((*content), i) != 1 /* && exp != 2 */)
			i++;
		else if ((*content)[i] == '\\' && check_quotes((*content), i) == 2 /* && exp != 2 */)
			i++;
		else if ((*content)[i] == '\'' && check_quotes((*content), i) != 2 /* && exp != 2 */)
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

int	remove_quotes(t_input *first)
{
	t_input	*cur;

	cur = first;
	while (cur)
	{
		if ((ft_strchr(cur->content, '\'') || ft_strchr(cur->content, '"')))
		{
			if (remove_useless_quotes(&(cur->content), return_final_len(cur->content, cur->exp), cur->exp) != 0)
				return (1);	
		}
		cur = cur->next;
		if (cur == first)
			break ;
	}
	return (0);
}
