/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:05:35 by apchelni          #+#    #+#             */
/*   Updated: 2024/09/10 19:05:37 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*p;

	p = (char *)s;
	while (n--)
	{
		*p = 0;
		p++;
	}
}
/*
#include <string.h>
int	main()
{
	char arr[10] = "Woop";

	printf("%s", arr);
	bzero(arr, 3);
	
	char arr2[10] = "Woop";

	printf("%s", arr2);
	ft_bzero(arr2, 3);
}*/