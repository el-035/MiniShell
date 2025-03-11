/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:50:52 by apchelni          #+#    #+#             */
/*   Updated: 2024/09/22 17:51:16 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/* 
#include <stdio.h>

void foo(unsigned int i, char *s)
{
	if (i % 2 == 0)
		*s = '*';
}

int main()
{
	char str[] = "Heyo";
	printf("%s\n", str);
	ft_striteri(str, foo);
	printf("%s", str);
} */