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

char    *ft_strnstr(const char *big, const char *little, size_t len)
{
        size_t  i;
        size_t  j;

        i = 0;
        j = 0;
        if (little[i] == '\0')
                return ((char *) &big[i]);
        while (big[i] && j < len)
        {
                j = 0;
                while (little[j] && big[i + j] == little[j] && j < len)
                {
                        j++;
                        if (little[j] == '\0')
                                return ((char *) &big[i]);
                }
                i++;
        }
        return (NULL);
}

/*
#include <stdio.h>
#include <bsd/string.h>
int	main()
{
	printf ("%s",  ft_strnstr("Hey you jy", "z", 30));
	printf ("%s",  strnstr("Hey you jy", "z", 30));
}*/