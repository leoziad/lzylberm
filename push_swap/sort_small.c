/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:26:46 by lzylberm          #+#    #+#             */
/*   Updated: 2021/11/25 13:38:44 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

void	sort_3(t_list **stack_a)
{
	t_list	*stack;

	stack = *stack_a;
	if ((*stack).i > (*stack).next->i && (*stack).next->i
		> (*stack).next->next->i && (*stack).next->next->i < (*stack).i)
	{
		sa(stack_a);
		rra(stack_a);
	}
	else if ((*stack).i > (*stack).next->i && (*stack).next->i
		< (*stack).next->next->i && (*stack).next->next->i < (*stack).i)
		ra(stack_a);
	else if ((*stack).i > (*stack).next->i && (*stack).next->i
		< (*stack).next->next->i && (*stack).next->next->i > (*stack).i)
		sa(stack_a);
	else if ((*stack).i < (*stack).next->i && (*stack).next->i
		> (*stack).next->next->i && (*stack).next->next->i < (*stack).i)
		rra(stack_a);
	else if ((*stack).i < (*stack).next->i && (*stack).next->i
		> (*stack).next->next->i && (*stack).next->next->i > (*stack).i)
	{
		sa(stack_a);
		ra(stack_a);
	}
}

void	sort_4(t_list **stack_a, t_list **stack_b)
{
	update_pos(stack_a);
	smart_rotate(stack_a, 0);
	pb(stack_a, stack_b);
	sort_3(stack_a);
	pa(stack_a, stack_b);
}

void	sort_5(t_list **stack_a, t_list **stack_b)
{
	update_pos(stack_a);
	smart_rotate(stack_a, 0);
	pb(stack_a, stack_b);
	update_pos(stack_a);
	smart_rotate(stack_a, 1);
	pb(stack_a, stack_b);
	sort_3(stack_a);
	pa(stack_a, stack_b);
	pa(stack_a, stack_b);
}
