/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:35:06 by apchelni          #+#    #+#             */
/*   Updated: 2024/09/26 20:35:13 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (0);
	new_node -> content = content;
	new_node -> next = NULL;
	return (new_node);
}
/* 
#include <stdio.h>
int main()
{
	char *str = "Hey you";

	t_list *node = ft_lstnew(str);
	printf ("%s", (char *)node -> content);
	free (node);
} */