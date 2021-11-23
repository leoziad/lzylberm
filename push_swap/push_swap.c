/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:34:00 by lzylberm          #+#    #+#             */
/*   Updated: 2021/11/23 18:05:38 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

char	*int_to_bin(int i)
{
	char	*bin_val;
	int		index;

	index = 0;
	bin_val = ft_strnew(32);
	if (i % 2 != 0)
		bin_val[index] = '1';
	index++;
	while (i > 1)
	{
		i = i / 2;
		if (i % 2 != 0)
			bin_val[index] = '1';
		index++;
	}
	return (bin_val);
}

void	bin_val(t_list **stack)
{
	t_list	*tmp;

	tmp = *stack;
	while (tmp)
	{
		tmp->bin = int_to_bin(tmp->content);
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv)
{
	t_list	*stack_a;
	t_list	*stack_b;
	int		i;

	i = 2;
	stack_a = ft_lstnew(ft_atoi(argv[1]));
	stack_b = NULL;
	while(i < argc)
	{
		ft_lstadd_back(&stack_a, ft_lstnew(ft_atoi(argv[i])));
		i++;
	}
	duplicates(&stack_a);
	create_index(&stack_a);
	if (argc == 4)
		sort_3(&stack_a);
	else if (argc == 5)
		sort_4(&stack_a, &stack_b);
	else if (argc == 6)
		sort_5(&stack_a, &stack_b);
	else
	{
		push_chunks(&stack_a, &stack_b);
		push_back_chunks(&stack_a, &stack_b);
	}
	free(stack_a);
	free(stack_b);
	return (0);
}
