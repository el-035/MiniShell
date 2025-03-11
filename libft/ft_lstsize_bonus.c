/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 18:45:15 by apchelni          #+#    #+#             */
/*   Updated: 2024/09/29 18:45:17 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 1;
	if (!lst)
		return (0);
	while (lst -> next != 0)
	{
		lst = lst -> next;
		size++;
	}
	return (size);
}
/* 
#include <stdio.h>

int	main()
{
	t_list *head = 0;
	t_list *n1;
	t_list *n2;
	t_list *n3;

	n1 = ft_lstnew ("1st");
	n2 = ft_lstnew ("2nd");
	n3 = ft_lstnew ("3d");
	ft_lstadd_back (&head, n1);
	ft_lstadd_back (&head, n2);
	ft_lstadd_back (&head, n3); 

	printf ("%d\n", (int)ft_lstsize(head));

 free (n1);
	free (n2);
	free (n3);
} */