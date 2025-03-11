/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isalnum.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:16:55 by apchelni          #+#    #+#             */
/*   Updated: 2024/09/03 17:16:59 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if ((c >= 97 && c <= 122)
		|| (c >= 65 && c <= 90)
		|| (c >= 48 && c <= 57))
		return (8);
	else
		return (0);
}
/*
#include <ctype.h>
#include <stdio.h>
int	main()
{
	printf("Is character: %d\n", isalnum('1'));

	printf("Custom is character: %d", ft_isalnum('1'));
}*/
