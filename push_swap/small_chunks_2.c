/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_chunks_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:29:58 by lzylberm          #+#    #+#             */
/*   Updated: 2021/11/24 19:36:34 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

void	chunk6_7(t_list **stack_a, t_list **stack_b, int size)
{
	t_list	*tmp;

	update_pos(stack_a);
	tmp = *stack_a;
	while (tmp)
	{
		if (tmp->i < (size / 7) * 6)
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

void	push_chunks_7(t_list **stack_a, t_list **stack_b)
{
	int	size;

	size = ft_lstsize(*stack_a);
	chunk1_7(stack_a, stack_b, size);
	chunk2_7(stack_a, stack_b, size);
	chunk3_7(stack_a, stack_b, size);
	chunk4_7(stack_a, stack_b, size);
	chunk5_7(stack_a, stack_b, size);
	chunk6_7(stack_a, stack_b, size);
	while (*stack_a)
		pb(stack_a, stack_b);
}
