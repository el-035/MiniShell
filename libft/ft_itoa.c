/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:36:40 by apchelni          #+#    #+#             */
/*   Updated: 2024/09/20 18:37:02 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_length(int n)
{
	int	length;
	int	negative;

	negative = 0;
	if (n < 0)
		negative = 1;
	if (n == 0)
		length = 1;
	else
	{
		length = 0 + negative;
		while (n != 0)
		{
			n /= 10;
			length++;
		}
	}
	return (length);
}

static void	put_num(int n, char *num, int length)
{
	while (n)
	{
		num[--length] = n % 10 + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*num;
	int		length;

	length = count_length(n);
	num = (char *)malloc(sizeof(char) * (length + 1));
	if (!num)
		return (0);
	num[length] = '\0';
	if (n == 0)
		num[0] = '0';
	if (n < 0)
	{
		if (n == -2147483648)
		{
			num[--length] = '8';
			n = -214748364;
		}
		n = -n;
		num[0] = '-';
	}
	put_num(n, num, length);
	return (num);
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