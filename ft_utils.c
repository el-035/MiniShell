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
