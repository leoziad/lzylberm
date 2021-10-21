/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:34:00 by lzylberm          #+#    #+#             */
/*   Updated: 2021/10/21 18:48:58 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

void	print_list(t_list *lst)
{
	while(lst)
	{
		ft_putnbr(lst->content);
		lst = lst->next;
	}
}

void	sa(t_list *stack_a)
{
	t_list	*tmp;
	
	tmp = NULL;
	if (ft_lstsize(stack_a) > 1)
	{
		tmp = stack_a->next->next;
		stack_a->next = stack_a->next->next;;
		stack_a->next->next = stack_a;
		free (tmp);
	}
}

int	main(int argc, char **argv)
{
	t_list	*stack_a;
//	t_list	*stack_b;
	int		i;

	i = 2;
	stack_a = ft_lstnew(ft_atoi(argv[1]));
	while(i < argc)
	{
		ft_lstadd_back(&stack_a, ft_lstnew(ft_atoi(argv[i])));
		i++;
	}
	print_list(stack_a);
	printf("\n");
	sa(stack_a);
	print_list(stack_a);

	return (0);
}
