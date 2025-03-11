/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:23:26 by apchelni          #+#    #+#             */
/*   Updated: 2024/09/03 17:23:29 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (2048);
	else
		return (0);
}
/*
#include <ctype.h>
#include <stdio.h>
int	main()
{
	printf("Is character: %d\n", isdigit('0'));

	printf("Custom is character: %d", ft_isdigit('a'));
}*/
