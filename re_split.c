#include "minishell.h"

int	count_word(char *content)
{
	int	 i;
	int	 wc;

	i = 0;
	wc = 0;
	if (!content)
		return (0);
	while (content[i])
	{
		while (content[i] && is_space(content[i]) == 1)
			i++;
		if (content[i] && is_space(content[i]) == 0)
		{
			wc++;
			while (content[i] && is_space(content[i]) == 0)
				i++;
		}
	}
	return (wc);
}
