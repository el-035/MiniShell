/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 21:27:04 by apchelni          #+#    #+#             */
/*   Updated: 2024/09/10 22:47:54 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(char *s, int c)
{
	int		length;
	char	*last;

	length = 0;
	last = 0;
	while (s[length])
		length++;
	while (length >= 0)
	{
		if (s[length] == (char)c)
		{
			last = &s[length];
			break ;
		}
		length--;
	}
	return ((char *)last);
}
/*
#include <string.h>
#include <stdio.h>

int	main()
{
	printf("%s", strrchr("heyeyeyea\n", 'y'));
	printf("%s", ft_strrchr("heyeyeyea", 'y'));
}*/
