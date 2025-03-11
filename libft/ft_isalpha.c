/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:54:29 by apchelni          #+#    #+#             */
/*   Updated: 2024/09/02 16:54:33 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90))
		return (1024);
	else
		return (0);
}
/*
#include <ctype.h>
#include <stdio.h>
int	main()
{
	printf("Is character: %d\n", isalpha('h'));

	printf("Custom is character: %d", ft_isalpha('h'));
}*/
