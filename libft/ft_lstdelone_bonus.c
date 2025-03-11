/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:10:54 by apchelni          #+#    #+#             */
/*   Updated: 2024/10/01 20:10:57 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst)
	{
		del(lst -> content);
		free(lst);
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
	ft_lstdelone(n1, del);
	printf ("%s", (char *)n1 -> content);
	printf ("%s", (char *)n2 -> content);
	ft_lstdelone(n2, del);
} */