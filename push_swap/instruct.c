/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:53:55 by lzylberm          #+#    #+#             */
/*   Updated: 2021/11/23 16:17:55 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

void	sa(t_list **stack_a)
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
	write(1, "sa\n", 3);
}

void	sb(t_list **stack_b)
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
	write(1, "sb\n", 3);
}

void	ss(t_list **stack_a, t_list **stack_b)
{
	sa(stack_a);
	sb(stack_b);
	write(1, "ss\n", 3);
}

void	pa(t_list **stack_a, t_list **stack_b)
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
	write(1, "pa\n", 3);
}

void	pb(t_list **stack_a, t_list **stack_b)
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
	write(1, "pb\n", 3);
}

void	ra(t_list **stack_a)
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
	write(1, "ra\n", 3);
}

void	rb(t_list **stack_b)
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
	write(1, "rb\n", 3);
}

void	rr(t_list **stack_a, t_list **stack_b)
{
	ra(stack_a);
	rb(stack_b);
	write(1, "rr\n", 3);
}

void	rra(t_list **stack_a)
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
	write(1, "rra\n", 4);
}

void	rrb(t_list **stack_b)
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
	write(1, "rrb\n", 4);
}

void	rrr(t_list **stack_a, t_list **stack_b)
{
	rra(stack_a);
	rrb(stack_b);
	write(1, "rrr\n", 4);
}
