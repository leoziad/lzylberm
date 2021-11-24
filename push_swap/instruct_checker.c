/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:53:55 by lzylberm          #+#    #+#             */
/*   Updated: 2021/11/24 19:37:44 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

void	sa_s(t_list **stack_a)
{
	t_list	*tmp1;
	t_list	*tmp2;

	tmp1 = NULL;
	tmp2 = NULL;
	if (ft_lstsize(*stack_a) > 1)
	{
		tmp1 = *stack_a;
		tmp2 = *stack_a;
		tmp1 = tmp1->next;
		*stack_a = tmp1;
		tmp2->next = tmp1->next;
		tmp1->next = tmp2;
	}
}

void	sb_s(t_list **stack_b)
{
	t_list	*tmp1;
	t_list	*tmp2;

	tmp1 = NULL;
	tmp2 = NULL;
	if (ft_lstsize(*stack_b) > 1)
	{
		tmp1 = *stack_b;
		tmp2 = *stack_b;
		tmp1 = tmp1->next;
		*stack_b = tmp1;
		tmp2->next = tmp1->next;
		tmp1->next = tmp2;
	}
}

void	ss_s(t_list **stack_a, t_list **stack_b)
{
	sa_s(stack_a);
	sb_s(stack_b);
}

void	pa_s(t_list **stack_a, t_list **stack_b)
{
	t_list	*tmp1;
	t_list	*tmp2;

	if (*stack_b)
	{
		tmp1 = *stack_b;
		tmp2 = tmp1->next;
		*stack_b = tmp2;
		tmp2 = *stack_a;
		*stack_a = tmp1;
		tmp1->next = tmp2;
	}
}

void	pb_s(t_list **stack_a, t_list **stack_b)
{
	t_list	*tmp1;
	t_list	*tmp2;

	if (*stack_a)
	{
		tmp1 = *stack_a;
		tmp2 = tmp1->next;
		*stack_a = tmp2;
		tmp2 = *stack_b;
		*stack_b = tmp1;
		tmp1->next = tmp2;
	}
}

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

	tmp1 = *stack_a;
	while (tmp1->next->next != NULL)
		tmp1 = tmp1->next;
	tmp2 = tmp1->next;
	tmp1->next = NULL;
	tmp2->next = *stack_a;
	*stack_a = tmp2;
}

void	rrb_s(t_list **stack_b)
{
	t_list	*tmp1;
	t_list	*tmp2;

	tmp1 = *stack_b;
	while (tmp1->next->next != NULL)
		tmp1 = tmp1->next;
	tmp2 = tmp1->next;
	tmp1->next = NULL;
	tmp2->next = *stack_b;
	*stack_b = tmp2;
}

void	rrr_s(t_list **stack_a, t_list **stack_b)
{
	rra_s(stack_a);
	rrb_s(stack_b);
}
