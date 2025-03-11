/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 18:23:02 by apchelni          #+#    #+#             */
/*   Updated: 2024/09/29 18:23:04 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (*lst == 0)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last -> next = new;
	}
}
/* 
#include <stdio.h>

int main()
{
	t_list *list = 0;
	t_list *n1;
	t_list *n2;
	t_list *p;

	n1 = ft_lstnew ("1st");
	n2 = ft_lstnew ("2nd");
	ft_lstadd_back (&list, n1);
	ft_lstadd_back (&list, n2);
	p = list;
	while (p != 0)
	{
		printf ("%s\n", (char *)p -> content);
		p = p -> next;
	}
	free (n1);
	free (n2);
} */