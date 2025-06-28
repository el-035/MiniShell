#include "minishell.h"

int	exp_helper(char *content)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (content[i])
	{
		if (content[i] == '$' && check_quotes(content, i) == 0)
			count++;
		i++;
	}
	if (count == 0)
		return (-1);
	return (count);
}

int	start_len(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '$')
		{
			if (content[i + 1] && (content[i + 1] == '$'))
				i += 2;
			else if (content[i + 1] && !(ft_isalnum(content[i + 1]) || content
					[i + 1] == '_'))
				i++;
			else if (check_quotes(content, i) == 1)
				i++;
			else
				return (i);
		}
		else
			i++;
	}
	return (i);
}
