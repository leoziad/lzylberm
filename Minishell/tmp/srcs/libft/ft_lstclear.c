/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:16:42 by lzylberm          #+#    #+#             */
/*   Updated: 2021/04/24 15:43:16 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list		*current;
	t_list		*next;

	current = *lst;
	while (current != NULL)
	{
		del(current->content);
		next = current->next;
		free (current);
		current = next;
	}
	(*lst) = NULL;
	lst = NULL;
}
