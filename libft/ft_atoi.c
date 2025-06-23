/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:46:54 by apchelni          #+#    #+#             */
/*   Updated: 2024/09/04 19:46:56 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

int	ft_atoi(const char *c)
{
	int	number;
	int	negative;

	number = 0;
	while (*c == 32 || (*c >= 9 && *c <= 13))
		c++;
	if (*c == '-' || *c == '+')
	{
		if (*c == '-')
			negative = 1;
		c++;
	}
	if (*c < '0' || *c > '9')
		return (0);
	while (*c)
	{
		if (*c >= '0' && *c <= '9')
			number = number * 10 + *c - '0';
		else
			break ;
		c++;
	}
	if (negative == 1)
		number = -number;
	return (number);
}

long	long_atoi(const char *str)
{
	int		i;
	long	result;
	int		n;

	n = 1;
	i = 0;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (ft_strncmp(&str[i], "-9223372036854775808", 20) == 0)
		return (LONG_MIN);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n = -1;
		i++;
	}
	if (str[i])
	{
		while (str[i] >= 48 && str[i] <= 57)
			result = result * 10 + str[i++] - 48;
	}
	return (result * n);
}

/* 
#include <stdlib.h>
#include <stdio.h>

int	main()
{
	printf ("%d\n", atoi("-123h"));
	printf ("%d", ft_atoi("-123h"));
}
 */