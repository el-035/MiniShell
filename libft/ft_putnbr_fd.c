/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:55:09 by apchelni          #+#    #+#             */
/*   Updated: 2024/09/09 20:55:11 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	s;

	if (n < 0)
	{
		if (n == -2147483648)
		{
			write (fd, "-2147483648", 11);
			return ;
		}
		else
		{
			n = -n;
			write (fd, "-", 1);
		}
	}
	if (n >= 0 && n <= 9)
	{
		s = n + '0';
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		s = n % 10 + '0';
	}
	write (fd, &s, 1);
}
/*
#include <fcntl.h>
int main()
{
	int fd = open("test.txt", O_WRONLY);
	ft_putnbr_fd(1067567, fd);
}*/