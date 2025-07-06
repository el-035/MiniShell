#include "minishell.h"

char	*double_join(char *s1, char *s2, char *s3) // those are not allocated
{													//DO NOT PUT FAIL MALL HERE
	char	*tmp;
	char	*final;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	final = ft_strjoin(tmp, s3);
	if (!final)
		return (free(tmp), NULL);
	return (free(tmp), final);
}