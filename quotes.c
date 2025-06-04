#include"minishell.h"

int	check_quotes(char *content, int len)
{
	int	quote;
	int i;

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

int return_final_len(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(str[i])
	{
		if (str[i] == '"'  && check_quotes(str, i) != 1)
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

int	dollar_sign(t_input *cur)
{
	char *temp;

	if (ft_strncmp(cur->content, "$\"", 2) != 0)
		return 0;
	temp = ft_strdup(cur->content + 1);
	if (!temp)
		return 1;	//error alloc
	free (cur->content);
	cur->content = temp;
}

int	remove_useless_quotes(t_input *cur)
{
	int i;
	int j;
	char *final;

	i = 0;
	dollar_sign(cur);
	j = return_final_len(cur->content);
	final = (char *) ft_calloc(j + 1, sizeof(char));
	j = 0;
	while(cur->content[i])
	{
		if (cur->content[i] == '"'  && check_quotes(cur->content, i) != 1)
			i++;
		else if (cur->content[i] == '\\' && check_quotes(cur->content, i) == 2)
			i++;
		else if (cur->content[i] == '\'' && check_quotes(cur->content, i) != 2)
			i++;
		else
			final[j++] = cur->content[i++];
	}
	free(cur->content);
	cur->content = ft_strdup(final);
	free(final);
	return 0;
}
