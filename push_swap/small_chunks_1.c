/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_chunks_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:29:03 by lzylberm          #+#    #+#             */
/*   Updated: 2021/12/07 16:56:44 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

void	chunk1_6(t_list **stack_a, t_list **stack_b, int size)
{
	t_list	*tmp;

	update_pos(stack_a);
	tmp = *stack_a;
	while (tmp)
	{
		if (tmp->i < size / 6)
		{
			smart_rotate_a(stack_a, tmp->i);
			pb(stack_a, stack_b);
			update_pos(stack_a);
			tmp = *stack_a;
		}
		else
			tmp = tmp->next;
	}
}

void	chunk2_6(t_list **stack_a, t_list **stack_b, int size)
{
	t_list	*tmp;

	update_pos(stack_a);
	tmp = *stack_a;
	while (tmp)
	{
		if (tmp->i < (size / 6) * 2)
		{
			smart_rotate_a(stack_a, tmp->i);
			pb(stack_a, stack_b);
			update_pos(stack_a);
			tmp = *stack_a;
		}
		else
			tmp = tmp->next;
	}
}

void	chunk3_6(t_list **stack_a, t_list **stack_b, int size)
{
	t_list	*tmp;

	update_pos(stack_a);
	tmp = *stack_a;
	while (tmp)
	{
		if (tmp->i < (size / 6) * 3)
		{
			smart_rotate_a(stack_a, tmp->i);
			pb(stack_a, stack_b);
			update_pos(stack_a);
			tmp = *stack_a;
		}
		else
			tmp = tmp->next;
	}
}

void	chunk4_6(t_list **stack_a, t_list **stack_b, int size)
{
	t_list	*tmp;

	update_pos(stack_a);
	tmp = *stack_a;
	while (tmp)
	{
		if (tmp->i < (size / 6) * 4)
		{
			smart_rotate_a(stack_a, tmp->i);
			pb(stack_a, stack_b);
			update_pos(stack_a);
			tmp = *stack_a;
		}
		else
			tmp = tmp->next;
	}
}

void	chunk5_6(t_list **stack_a, t_list **stack_b, int size)
{
	t_list	*tmp;

	update_pos(stack_a);
	tmp = *stack_a;
	while (tmp)
	{
		if (tmp->i < (size / 6) * 5)
		{
			smart_rotate_a(stack_a, tmp->i);
			pb(stack_a, stack_b);
			update_pos(stack_a);
			tmp = *stack_a;
		}
		else
			tmp = tmp->next;
	}
}
