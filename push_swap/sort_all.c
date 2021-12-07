/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:34:30 by lzylberm          #+#    #+#             */
/*   Updated: 2021/11/26 18:45:47 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

void	smart_rotate(t_list **stack, int i)
{
	int		size;
	int		count;
	t_list	*tmp;

	size = ft_lstsize(*stack);
	tmp = *stack;
	while (tmp->i != i)
		tmp = tmp->next;
	count = size - tmp->pos;
	if (count > size / 2)
	{
		while (count < size)
		{
			ra(stack);
			count++;
		}
	}
	else
	{
		while (count > 0)
		{
			rra(stack);
			count--;
		}
	}
}

void	push_back_chunks(t_list **stack_a, t_list **stack_b)
{
	int	size;

	size = ft_lstsize(*stack_b) - 1;
	update_pos(stack_b);
	while (size >= 0)
	{
		smart_rotate(stack_b, size);
		pa(stack_a, stack_b);
		update_pos(stack_b);
		size--;
	}
}
