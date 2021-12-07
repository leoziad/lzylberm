/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_chunks_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:29:58 by lzylberm          #+#    #+#             */
/*   Updated: 2021/12/07 14:45:41 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

void	push_chunks_6(t_list **stack_a, t_list **stack_b)
{
	int	size;

	size = ft_lstsize(*stack_a);
	chunk1_6(stack_a, stack_b, size);
	chunk2_6(stack_a, stack_b, size);
	chunk3_6(stack_a, stack_b, size);
	chunk4_6(stack_a, stack_b, size);
	chunk5_6(stack_a, stack_b, size);
	while (*stack_a)
		pb(stack_a, stack_b);
}
