/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:27:49 by apchelni          #+#    #+#             */
/*   Updated: 2024/09/19 22:28:29 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	find_length(char const *s)
{
	size_t	length;

	length = 0;
	while (s[length])
		length++;
	return (length);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	real_length;
	size_t	i;

	i = 0;
	if (start >= find_length(s))
	{
		substr = (char *)malloc(1);
		if (substr)
			substr[0] = '\0';
		return (substr);
	}
	real_length = find_length(s) - start;
	if (len > real_length)
		len = real_length;
	substr = (char *)malloc(len + 1);
	if (substr == 0)
		return (0);
	while (len-- && s[start + i] != '\0')
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
/* 
#include <stdio.h>

int	main()
{
	printf("%s", ft_substr("", 0, 15));
} */
