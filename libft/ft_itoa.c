/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:33:59 by efittant          #+#    #+#             */
/*   Updated: 2024/09/13 18:34:01 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>
#include <limits.h>

static int	ft_intlen(long n)
{
	int	mem;

	mem = 0;
	if (n == LONG_MIN)
		return (20);
	if (n <= 0)
	{
		mem++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		mem++;
	}
	return (mem);
}

char	*ft_itoa(long n)
{
	char	*arr;
	int		mem;

	mem = ft_intlen(n);
	if (n == LONG_MIN)
		return (ft_strdup("-9223372036854775808"));
	else
		arr = (char *) ft_calloc((mem + 1), sizeof(char));
	if (arr == NULL)
		return (NULL);
	if (n < 0 && n > LONG_MIN)
	{
		n *= -1;
		arr[0] = '-';
	}
	if (n == 0)
		arr[0] = '0';
	while (mem > 0 && arr[mem - 1] != '-' && n != 0 && n != LONG_MIN)
	{
		mem--;
		arr[mem] = (n % 10) + 48;
		n /= 10;
	}
	return (arr);
}

/* 
#include <stdio.h>
int main()
{
	char *res;
	
	res = ft_itoa(1);
	printf ("%s", res);
	free (res);
} */