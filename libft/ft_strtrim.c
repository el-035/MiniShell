/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:21:58 by apchelni          #+#    #+#             */
/*   Updated: 2024/09/20 12:22:15 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_length(char const *str)
{
	int	length;

	length = 0;
	while (str[length])
		length++;
	return (length);
}

static int	is_set(char s1, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s1)
			return (1);
		i++;
	}
	return (0);
}

static int	find_start(char const *s1, char const *set)
{
	int	start;

	start = 0;
	while (s1[start] && is_set(s1[start], set))
		start++;
	return (start);
}

static int	find_end(char const *s1, char const *set, int start)
{
	int	end;

	end = find_length(s1) - 1;
	while (end >= start && is_set(s1[end], set))
		end--;
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_str;
	int		start;
	int		end;
	int		length;
	int		i;

	i = -1;
	if (*s1 == '\0')
	{
		new_str = ft_calloc(1, sizeof(char));
		if (!new_str)
			return (0);
		return (new_str);
	}
	start = find_start(s1, set);
	end = find_end(s1, set, start);
	length = end - start + 1;
	new_str = ft_calloc(length + 1, sizeof(char));
	if (!new_str)
		return (0);
	while (++i < length)
		new_str[i] = s1[start + i];
	return (new_str);
}
/* 
#include <stdio.h>
int	main()
{
	char *str;
	str = ft_strtrim("ihii", "");
	printf("%s", str);
	free (str);
} */