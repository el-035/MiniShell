/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 21:59:04 by apchelni          #+#    #+#             */
/*   Updated: 2024/09/10 21:59:06 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;
	unsigned char		uc;

	p = (const unsigned char *)s;
	uc = (unsigned char)c;
	while (n--)
	{
		if (*p == uc)
			return ((void *)p);
		p++;
	}
	return (0);
}
/*
#include <string.h>
int	main()
{
	unsigned char arr[] = "Hey you";
	unsigned char c = 'c';

	printf ("%s", (char *)memchr(arr, c, 7));
	printf ("%s", (char *)ft_memchr(arr, c, 7));
}*/
