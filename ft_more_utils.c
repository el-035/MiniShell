#include "minishell.h"

char	*double_join(char *s1, char *s2, char *s3) // those are not allocated
{													//DO NOT PUT FAIL MALL HERE
	char	*final;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	if (len == 0)
		return (ft_strdup(""));
	final = (char *) ft_calloc(len + 1, sizeof(char));
	if (!final)
		return (NULL);
	while (s1 && s1[i] && j < len)
		final[j++] = s1[i++];
	i = 0;
	while (s2 && s2[i] && j < len)
		final[j++] = s2[i++];
	i = 0;
	while (s3 && s3[i] && j < len)
		final[j++] = s3[i++];
	return (final);
}