/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:22:10 by apchelni          #+#    #+#             */
/*   Updated: 2024/10/01 22:22:12 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst)
	{
		while (lst)
		{
			f(lst -> content);
			lst = lst -> next;
		}
	}
}
/* 
#include <stdio.h>
void	print(void *content)
{
	printf ("%s", (char *)content);
}


int	main()
{
	t_list *head = 0;
	t_list *n1;
	t_list *n2;

	n1 = ft_lstnew (ft_strdup("1st"));
	n2 = ft_lstnew (ft_strdup("2st"));
	ft_lstadd_back (&head, n1);
	ft_lstadd_back (&head, n2);
	ft_lstiter(head, print);
} */