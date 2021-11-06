/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:34:00 by lzylberm          #+#    #+#             */
/*   Updated: 2021/11/06 18:48:00 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

/*void	print_list(t_list *lst)
{
	while(lst)
	{
		ft_putnbr(lst->content);
		lst = lst->next;
	}
}*/

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
}

void	ss(t_list **stack_a, t_list **stack_b)
{
	sa(stack_a);
	sb(stack_b);
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
}

void	rr(t_list **stack_a, t_list **stack_b)
{
	ra(stack_a);
	rb(stack_b);
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
}

void	rrr(t_list **stack_a, t_list **stack_b)
{
	rra(stack_a);
	rrb(stack_b);
}

void	duplicates(t_list **stack, char *error)
{
	t_list	*tmp1;
	t_list	*tmp2;

	tmp1 = *stack;
	while (tmp1->next->next != NULL) 
	{
		tmp2 = tmp1;
		while (tmp2->next != NULL)
		{
			tmp2 = tmp2->next;
			if (tmp2->content == tmp1->content)
			{
				*error = 1;
				return ;
			}
		}
		tmp1 = tmp1->next;
	}
}

int	main(int argc, char **argv)
{
	t_list	*stack_a;
//	t_list	*stack_b;
	char	error;
	int		i;

	error = 0;
	i = 2;
	stack_a = ft_lstnew(ft_atoi(argv[1], &error));
	while(i < argc)
	{
		ft_lstadd_back(&stack_a, ft_lstnew(ft_atoi(argv[i], &error)));
		i++;
	}
	duplicates(&stack_a, &error);
	if (error == 1)
	{
		write(2, "Error\n", 6);
	}
	
	return (0);
}
