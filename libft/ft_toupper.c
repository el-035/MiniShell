/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:32:23 by apchelni          #+#    #+#             */
/*   Updated: 2024/09/04 19:32:24 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	else
		return (c);
}
/*
#include <ctype.h>
#include <stdio.h>
int	main()
{
	printf ("%c", toupper(99));
	printf ("%c", ft_toupper(99));
}*/