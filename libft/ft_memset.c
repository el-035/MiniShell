/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:21:38 by apchelni          #+#    #+#             */
/*   Updated: 2024/09/10 18:21:41 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n--)
	{
		*p = (unsigned char)c;
		p++;
	}
	return (s);
}
/* 
#include <stdio.h>
#include <string.h>
int main()
{
	char	arr[10] = "HEY";
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%c", arr[i]);
		i++;
	}
	memset(arr + 3, '*', 1);
	printf("\n%s\n\n", arr);

	char	arr2[10] = "HEY";
	int	j;

	j = 0;
	while (arr2[j])
	{
		printf("%c", arr2[j]);
		j++;
	}
	ft_memset(arr2 + 3, '*', 1);
	printf("\n%s", arr2);
}
 */