/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:41:47 by apchelni          #+#    #+#             */
/*   Updated: 2024/09/09 13:41:49 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	compare_strings(const char *big, const char *little, size_t len)
{
	size_t	j;

	j = 0;
	while (big[j] && little[j] && big[j] == little[j] && j < len)
		j++;
	if (!little[j])
		return (1);
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		if (compare_strings(big + i, little, len - i))
			return ((char *)big + i);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <bsd/string.h>
int	main()
{
	printf ("%s",  ft_strnstr("Hey you jy", "z", 30));
	printf ("%s",  strnstr("Hey you jy", "z", 30));
}*/