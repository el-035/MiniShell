/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 21:48:15 by apchelni          #+#    #+#             */
/*   Updated: 2024/10/01 21:48:17 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	if (lst)
	{
		current = *lst;
		while (current)
		{
			next = current -> next;
			ft_lstdelone(current, del);
			current = next;
		}
		*lst = 0;
	}
}
/* 
void	del(void *content)
{
	free(content);
}

#include <stdio.h>
int	main()
{
	t_list *head = 0;
	t_list *n1;
	t_list *n2;

	n1 = ft_lstnew (ft_strdup("1st"));
	n2 = ft_lstnew (ft_strdup("2st"));
	ft_lstadd_back (&head, n1);
	ft_lstadd_back (&head, n2);
	ft_lstclear(&head, del);
	if (head == 0)
		printf ("empty");
} */