/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:26:59 by apchelni          #+#    #+#             */
/*   Updated: 2024/09/22 17:27:57 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_str;
	int		length;
	int		i;

	i = 0;
	length = 0;
	if (!s || !f)
		return (0);
	while (s[length])
		length++;
	new_str = (char *)malloc(sizeof(char) * length + 1);
	if (!new_str)
		return (0);
	while (s[i])
	{
		new_str[i] = f(i, s[i]);
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
/* 
#include <stdio.h>

char foo(unsigned int i, char c)
{
	if (i % 2 == 0)
		c = '*';
	return (c);
}

int main()
{
	char str[] = "Heyo";
	printf("%s\n", str);
	printf("%s", ft_strmapi(str, foo));
} */