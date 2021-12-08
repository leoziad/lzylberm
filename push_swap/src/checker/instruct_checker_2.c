/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct_checker_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:13:24 by lzylberm          #+#    #+#             */
/*   Updated: 2021/11/26 14:29:44 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

void	ra_s(t_list **stack_a)
{
	t_list	*tmp1;
	t_list	*tmp2;

	if (ft_lstsize(*stack_a) > 1)
	{
		tmp1 = *stack_a;
		*stack_a = tmp1->next;
		tmp2 = ft_lstlast(*stack_a);
		tmp2->next = tmp1;
		tmp1->next = NULL;
	}
}

void	rb_s(t_list **stack_b)
{
	t_list	*tmp1;
	t_list	*tmp2;

	if (ft_lstsize(*stack_b) > 1)
	{
		tmp1 = *stack_b;
		*stack_b = tmp1->next;
		tmp2 = ft_lstlast(*stack_b);
		tmp2->next = tmp1;
		tmp1->next = NULL;
	}
}

void	rr_s(t_list **stack_a, t_list **stack_b)
{
	ra_s(stack_a);
	rb_s(stack_b);
}

void	rra_s(t_list **stack_a)
{
	t_list	*tmp1;
	t_list	*tmp2;

	if (ft_lstsize(*stack_a) > 1)
	{
		tmp1 = *stack_a;
		while (tmp1->next->next != NULL)
			tmp1 = tmp1->next;
		tmp2 = tmp1->next;
		tmp1->next = NULL;
		tmp2->next = *stack_a;
		*stack_a = tmp2;
	}
}

void	rrb_s(t_list **stack_b)
{
	t_list	*tmp1;
	t_list	*tmp2;

	if (ft_lstsize(*stack_b) > 1)
	{
		tmp1 = *stack_b;
		while (tmp1->next->next != NULL)
			tmp1 = tmp1->next;
		tmp2 = tmp1->next;
		tmp1->next = NULL;
		tmp2->next = *stack_b;
		*stack_b = tmp2;
	}
}
