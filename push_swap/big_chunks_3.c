/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_chunks_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:32:33 by lzylberm          #+#    #+#             */
/*   Updated: 2021/11/25 12:40:10 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

void	chunk11_13(t_list **stack_a, t_list **stack_b, int size)
{
	t_list	*tmp;

	update_pos(stack_a);
	tmp = *stack_a;
	while (tmp)
	{
		if (tmp->i < (size / 13) * 11)
		{
			smart_rotate(stack_a, tmp->i);
			pb(stack_a, stack_b);
			update_pos(stack_a);
			tmp = *stack_a;
		}
		else
			tmp = tmp->next;
	}
}

void	chunk12_13(t_list **stack_a, t_list **stack_b, int size)
{
	t_list	*tmp;

	update_pos(stack_a);
	tmp = *stack_a;
	while (tmp)
	{
		if (tmp->i < (size / 13) * 12)
		{
			smart_rotate(stack_a, tmp->i);
			pb(stack_a, stack_b);
			update_pos(stack_a);
			tmp = *stack_a;
		}
		else
			tmp = tmp->next;
	}
}

void	push_chunks_13(t_list **stack_a, t_list **stack_b)
{
	int	size;

	size = ft_lstsize(*stack_a);
	chunk1_13(stack_a, stack_b, size);
	chunk2_13(stack_a, stack_b, size);
	chunk3_13(stack_a, stack_b, size);
	chunk4_13(stack_a, stack_b, size);
	chunk5_13(stack_a, stack_b, size);
	chunk6_13(stack_a, stack_b, size);
	chunk7_13(stack_a, stack_b, size);
	chunk8_13(stack_a, stack_b, size);
	chunk9_13(stack_a, stack_b, size);
	chunk10_13(stack_a, stack_b, size);
	chunk11_13(stack_a, stack_b, size);
	chunk12_13(stack_a, stack_b, size);
	while (*stack_a)
		pb(stack_a, stack_b);
}
