/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:14:32 by efittant          #+#    #+#             */
/*   Updated: 2024/10/30 15:14:35 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc_gnl(size_t nmemb, size_t size)
{
	unsigned char	*mem;
	size_t			temp;
	size_t			i;

	i = 0;
	temp = (nmemb * size);
	if (nmemb != 0 && temp / nmemb != size)
		return (NULL);
	mem = malloc(nmemb * size);
	if (mem == NULL)
		return (NULL);
	while (i < temp)
		mem[i++] = '\0';
	return ((void *)mem);
}

char	*ft_strchr_gnl(char *s, int c)
{
	int	i;

	i = 0;
	if (!s || !s[i])
		return (NULL);
	while (s[i])
	{
		if (s[i] == (unsigned char) c)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == (unsigned char) c)
		return ((char *) &s[i]);
	return (NULL);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*join;
	int		len1;
	int		len2;
	int		i;
	char	*ptr;

	len1 = 0;
	len2 = 0;
	i = 0;
	ptr = s1;
	while (ptr != NULL && ptr[len1])
		len1++;
	while (s2[len2])
		len2++;
	join = (char *)malloc((len1 + len2 + 1) * sizeof (char));
	if (!join)
		return (free (s1), s1 = NULL, NULL);
	while (ptr && len1-- > 0)
		join[i++] = *ptr++;
	while (len2-- > 0)
		join[i++] = *s2++;
	join[i] = '\0';
	return (free(s1), s1 = NULL, join);
}

char	*ft_strdup_gnl(char *s)
{
	int		i;
	char	*str;
	int		len;

	i = 0;
	len = 0;
	while (s[len])
		len++;
	str = (char *) ft_calloc_gnl((len + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = s[i];
	return (str);
}

//#include <stdio.h>
// int main (void)
// {
// 	//char *beg = NULL;
// 	char *end = "Nel mezzo del cammin di nostra vita \nmi ritrovai";

// 	printf ("%s", current_line(end));

// }
