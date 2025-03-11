/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 21:10:34 by apchelni          #+#    #+#             */
/*   Updated: 2024/09/10 22:35:36 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*p_d;
	const char	*p_s;

	p_d = (char *)dest;
	p_s = (const char *)src;
	if (p_d < p_s)
		while (n--)
			*p_d++ = *p_s++;
	else if (p_d > p_s)
	{
		p_d += n;
		p_s += n;
		while (n--)
			*(--p_d) = *(--p_s);
	}
	return (dest);
}
/*
#include <string.h>
int	main()
{
	char s1[10] = "Hey";
	char s2[] = "Hi";

	printf("%s\n", s1);
	memmove(s1, s2, 5);
	printf("%s\n\n", s1);

	char s3[10] = "Hey";
	char s4[] = "Hi";

	printf("%s\n", s3);
	ft_memmove(s3, s4, 5);
	printf("%s\n\n", s3);
}*/
