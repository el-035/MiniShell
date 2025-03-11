/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:59:19 by apchelni          #+#    #+#             */
/*   Updated: 2024/09/03 17:59:22 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (16384);
	else
		return (0);
}
/*
#include <ctype.h>
#include <stdio.h>
int	main()
{
	printf ("%d\n", isprint(31));
	printf ("%d", ft_isprint(31));
}*/