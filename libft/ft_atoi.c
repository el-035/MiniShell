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
/* 
#include <stdlib.h>
#include <stdio.h>

int	main()
{
	printf ("%d\n", atoi("-123h"));
	printf ("%d", ft_atoi("-123h"));
}
 */