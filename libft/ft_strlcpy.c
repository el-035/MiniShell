/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:16:53 by apchelni          #+#    #+#             */
/*   Updated: 2024/09/03 20:16:54 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	length;

	i = 0;
	length = 0;
	while (src[length])
		length++;
	if (size != 0)
	{
		while (i < size - 1 && i < length)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (length);
}
/*
#include <bsd/string.h>
int	main()
{
	char src[] = "Hello ";
	char dst[] = "you";

	char src2[] = "Hello ";
	char dst2[] = "you";
	printf("%s\n", dst);
	printf("%zu\n", strlcpy(dst, src, 0));
	printf("%s\n\n", dst);

	printf("%s\n", dst2);
	printf("%zu\n", ft_strlcpy(dst2, src2, ));
	printf("%s\n\n", dst2);
}*/
