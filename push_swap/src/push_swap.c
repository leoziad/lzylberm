/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:34:00 by lzylberm          #+#    #+#             */
/*   Updated: 2021/12/14 19:19:57 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

static t_list	*create_stack(int argc, char **argv)
{
	t_list	*stack;
	int		i;

	i = 2;
	stack = NULL;
	stack = ft_lstnew(ft_atoi(argv[1], &stack));
	while (i < argc)
	{
		ft_lstadd_back(&stack, ft_lstnew(ft_atoi(argv[i], &stack)));
		i++;
	}
	duplicates(&stack);
	create_index(&stack);
	return (stack);
}

void	sort_small(int argc, t_list **stack_a, t_list **stack_b)
{
	if (argc == 3)
		sort_2(stack_a);
	else if (argc == 4)
		sort_3(stack_a);
	else if (argc == 5)
		sort_4(stack_a, stack_b);
	else if (argc == 6)
		sort_5(stack_a, stack_b);
}

static int	check_sort(t_list *stack_a)
{
	int		i;

	while (stack_a->next != NULL)
	{
		i = stack_a->content;
		stack_a = stack_a->next;
		if (stack_a->content < i)
			return (0);
	}
	exit(0);
}

int	main(int argc, char **argv)
{
	t_list	*stack_a;
	t_list	*stack_b;

	if (argc > 1)
	{
		stack_a = create_stack(argc, argv);
		check_sort(stack_a);
		stack_b = NULL;
		if (argc < 7)
			sort_small(argc, &stack_a, &stack_b);
		else if (argc < 102)
		{
			push_chunks_6(&stack_a, &stack_b);
			push_back_chunks(&stack_a, &stack_b);
		}
		else
		{
			push_chunks_13(&stack_a, &stack_b);
			push_back_chunks(&stack_a, &stack_b);
		}
		ft_lstclear(&stack_a);
		ft_lstclear(&stack_b);
	}
	return (0);
}
