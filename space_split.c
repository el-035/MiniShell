/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <efittant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:40:02 by efittant          #+#    #+#             */
/*   Updated: 2025/07/11 19:02:46 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_strings(char const *s)
{
	int	i;
	int	num;
	int	string;

	i = 0;
	num = 0;
	string = 0;
	while (s[i] != '\0')
	{
		if (!is_space(s[i]) && !string)
		{
			string = 1;
			num++;
		}
		else if (is_space(s[i]))
			string = 0;
		i++;
	}
	return (num);
}

static char	*copy_str(char const *s, char *start)
{
	char	*str;
	int		length;
	int		i;

	length = s - start;
	i = 0;
	str = (char *)malloc(sizeof(char) * (length + 1));
	if (!str)
		return (0);
	while (i < length)
	{
		str[i] = start[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	**free_mem(char **res, int i)
{
	while (i-- > 0)
		free(res[i]);
	free(res);
	return (0);
}

char	**space_split(char const *s)
{
	char	**res;
	int		i;
	char	*start;

	i = 0;
	res = (char **)malloc(sizeof(char *) * (count_strings(s) + 1));
	if (!res)
		return (0);
	while (*s)
	{
		if (!is_space(*s))
		{
			start = (char *)s;
			while (*s && !is_space(*s))
				s++;
			res[i] = copy_str(s, start);
			if (!res[i])
				return (free_mem(res, i));
			i++;
		}
		else
			s++;
	}
	res[i] = 0;
	return (res);
}

/* static char	*word(char *s, int i)
{
	char	*word;
	int		j;

	j = 0;
	while (is_space(s[i]) == 1 && s[i])
		i++;
	while (is_space(s[i]) == 0 && s[i])
	{
		i++;
		j++;
	}
	word = (char *)malloc((j + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = i - j;
	j = 0;
	while (is_space(s[i]) == 0 && s[i])
		word[j++] = s[i++];
	word[j] = '\0';
	return (word);
}

char	**space_split(char const *s)
{
	int		wc;
	int		i;
	int		j;
	char	**split;

	wc = count_word((char *)s);
	i = 0;
	j = 0;
	split = (char **)ft_calloc((wc + 1), sizeof(char *));
	if (!split)
		return (NULL);
	else
	{
		while (s && split && j < wc)
		{
			split[j++] = word((char *)s, i);
			if (!split[j - 1])
				return (free_split(split), NULL);
			while (is_space(s[i]) == 1)
				i++;
			i = i + ft_strlen(split[j - 1]) + 1;
		}
	}
	return (split);
} */
