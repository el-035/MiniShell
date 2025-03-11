/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:07:08 by apchelni          #+#    #+#             */
/*   Updated: 2024/09/29 15:07:10 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new -> next = *lst;
	*lst = new;
}
/* 
#include <stdio.h>

int	main()
{
	t_list *n1;
	t_list *n2;
	t_list *n3;
	
	n1 = ft_lstnew("1st");
	n2 = ft_lstnew("2d");
	n3 = ft_lstnew("3d");
	ft_lstadd_front(&n1, n2);
	ft_lstadd_front(&n2, n3);
	t_list *tmp = n3;
	
	while (tmp != 0)
	{
		printf ("%s\n", (char *)tmp -> content);
		tmp = tmp -> next;
	}
	free (n1);
	free (n2);
	free (tmp);
	//free (n3);
} */