#include "minishell.h"

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
	{
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return 1;
	return 0;	
}

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