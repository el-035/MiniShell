/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:55:07 by efittant          #+#    #+#             */
/*   Updated: 2024/09/18 15:55:09 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* #include <stdlib.h>
#include "libft.h"

static int	is_deliminitor(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return 1;
	return 0;
}

static int	ft_word_count(char *s)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (s[i])
	{
		while (is_deliminitor(s[i]) == 1 && s[i])
			i++;
		if (is_deliminitor(s[i]) == 1 && s[i])
		{
			wc++;
			i++;
		}
		while (is_deliminitor(s[i]) == 1 && s[i])
			i++;
	}
	return (wc);
}

static char	*ft_word(char *s, int i)
{
	char	*word;
	int		j;

	j = 0;
	while (is_deliminitor(s[i]) == 1 && s[i])
		i++;
	while (is_deliminitor(s[i]) == 0 && s[i])
	{
		i++;
		j++;
	}
	word = (char *) malloc((j + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = i - j;
	j = 0;
	while (is_deliminitor(s[i]) == 0 && s[i])
		word[j++] = s[i++];
	word[j] = '\0';
	return (word);
}

static char	**ft_free(char **split)
{
	int	word;

	word = 0;
	while (split[word])
	{
		free(split[word]);
		word++;
	}
	free(split);
	return (NULL);
}

char	**ft_another_split(char const *s)
{
	int		wc;
	int		i;
	int		j;
	char	**split;

	wc = ft_word_count((char *) s);
	i = 0;
	j = 0;
	split = (char **) malloc ((wc + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	else
	{
		while (s && split && j < wc)
		{
			split[j++] = ft_word((char *)s, i);
			if (!split[j - 1])
				return (ft_free(split));
			while (is_deliminitor(s[i]) == 1)
				i++;
			i = i + ft_strlen(split[j - 1]) + 1;
		}
	}
	split[j] = 0;
	return (split);
}
 */