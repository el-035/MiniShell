/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:35:20 by apchelni          #+#    #+#             */
/*   Updated: 2024/09/10 22:36:11 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*p_d;
	const char	*p_s;

	if ((!src && !dest) || n == 0)
		return (dest);
	p_d = (char *) dest;
	p_s = (const char *) src;
	i = 0;
	while (i < n)
	{
		p_d[i] = p_s[i];
		i++;
	}
	return (dest);
}
/* 
#include <string.h>
#include <stdio.h>
int	main()
{
	char s1[] = "";
	char s2[] = "Hi";

	printf("%s\n", s1);
	memcpy(s1, s2, 1);
	printf("%s\n\n", s1);

	char s3[] = "";
	char s4[] = "Hi";

	printf("%s\n", s3);
	ft_memcpy(s3, s4, 1);
	printf("%s\n\n", s3);
} */
