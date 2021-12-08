/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_chunks_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:31:41 by lzylberm          #+#    #+#             */
/*   Updated: 2021/12/07 15:02:34 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

void	chunk1_13(t_list **stack_a, t_list **stack_b, int size)
{
	t_list	*tmp;

	update_pos(stack_a);
	tmp = *stack_a;
	while (tmp)
	{
		if (tmp->i < (size / 13))
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

void	chunk2_13(t_list **stack_a, t_list **stack_b, int size)
{
	t_list	*tmp;

	update_pos(stack_a);
	tmp = *stack_a;
	while (tmp)
	{
		if (tmp->i < (size / 13) * 2)
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

void	chunk3_13(t_list **stack_a, t_list **stack_b, int size)
{
	t_list	*tmp;

	update_pos(stack_a);
	tmp = *stack_a;
	while (tmp)
	{
		if (tmp->i < (size / 13) * 3)
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

void	chunk4_13(t_list **stack_a, t_list **stack_b, int size)
{
	t_list	*tmp;

	update_pos(stack_a);
	tmp = *stack_a;
	while (tmp)
	{
		if (tmp->i < (size / 13) * 4)
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

void	chunk5_13(t_list **stack_a, t_list **stack_b, int size)
{
	t_list	*tmp;

	update_pos(stack_a);
	tmp = *stack_a;
	while (tmp)
	{
		if (tmp->i < (size / 13) * 5)
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
