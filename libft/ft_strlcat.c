/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:55:46 by apchelni          #+#    #+#             */
/*   Updated: 2024/09/04 12:55:47 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	find_length(char *str)
{
	size_t	length;

	length = 0;
	while (str[length])
		length++;
	return (length);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_length;
	size_t	dst_length;
	size_t	i;
	size_t	j;

	j = 0;
	src_length = find_length((char *)src);
	dst_length = find_length(dst);
	if (size <= dst_length)
		return (src_length + size);
	i = dst_length;
	while (i < size - 1 && src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (src_length + dst_length);
}
/* 
#include <bsd/string.h>
#include <stdio.h>

int	main()
{
	char src[] = "hey";
	char dst[10] = "you";
	printf("%s\n", dst);
	printf("%zu\n", strlcat(dst, src, -1));
	printf("%s\n\n", dst);

	char src2[] = "hey";
	char dst2[10] = "you";
	printf("%s\n", dst2);
	printf("%zu\n", ft_strlcat(dst2, src2, -1));
	printf("%s\n\n", dst2);
} */