/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:34:30 by lzylberm          #+#    #+#             */
/*   Updated: 2021/12/14 19:18:58 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

void	smart_rotate_a(t_list **stack, int i)
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

void	smart_rotate_b(t_list **stack, int i)
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
			rb(stack);
			count++;
		}
	}
	else
	{
		while (count > 0)
		{
			rrb(stack);
			count--;
		}
	}
}

int	check_pos(t_list **stack, int i)
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
		return (size - count);
	else
		return (count);
}

void	smart_push_back(t_list **stack_a, t_list **stack_b, int *size)
{
	smart_rotate_b(stack_b, (*size) - 1);
	pa(stack_a, stack_b);
	update_pos(stack_b);
	smart_rotate_b(stack_b, *size);
	pa(stack_a, stack_b);
	sa(stack_a);
	update_pos(stack_b);
	*size -= 2;
}

void	push_back_chunks(t_list **stack_a, t_list **stack_b)
{
	int	size;

	size = ft_lstsize(*stack_b) - 1;
	update_pos(stack_b);
	while (size > 0)
	{
		if (check_pos(stack_b, size) <= check_pos(stack_b, size - 1))
		{
			smart_rotate_b(stack_b, size);
			pa(stack_a, stack_b);
			update_pos(stack_b);
			size--;
		}
		else
			smart_push_back(stack_a, stack_b, &size);
	}
	pa(stack_a, stack_b);
}
