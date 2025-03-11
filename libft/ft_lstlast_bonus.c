/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:50:41 by apchelni          #+#    #+#             */
/*   Updated: 2024/09/29 16:50:46 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst -> next != 0)
		lst = lst -> next;
	return (lst);
}
/* 
#include <stdio.h>

static t_list    *ft_lstnew2(void *content, t_list *next_node)
{
    t_list    *new_node;

    new_node = (t_list *)malloc(sizeof(t_list));
    if (!new_node)
        return (0);
    new_node -> content = content;
    new_node -> next = next_node;
    return (new_node);
}

int	main()
{
	t_list *n1;
	t_list *n2;
	t_list *n3;

	n3 = ft_lstnew2("3d", 0);
	n2 = ft_lstnew2("2d", n3);
	n1 = ft_lstnew2("1st", n2);

	t_list *last = ft_lstlast(n1);
		printf ("%s\n", (char *)last -> content);
	free (n1);
	free (n2);
	free (n3);
} */