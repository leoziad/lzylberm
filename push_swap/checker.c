/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:46:17 by lzylberm          #+#    #+#             */
/*   Updated: 2021/11/18 21:24:53 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

void	print_list(t_list *lst)
{
	while(lst)
	{
		ft_putnbr(lst->content);
		write(1, " ", 1);
		lst = lst->next;
	}
}

t_list	*create_stack(int argc, char **argv)
{
	t_list	*stack;
	char	error;
	int		i;

	error = 0;
	i = 2;
	stack = ft_lstnew(ft_atoi(argv[1], &error));
	while(i < argc)
	{
		ft_lstadd_back(&stack, ft_lstnew(ft_atoi(argv[i], &error)));
		i++;
	}
	duplicates(&stack, &error);
	if (error == 1)
		write(2, "Error\n", 6);
	return (stack);
}

t_list	*list_instruct(char *buff)
{
	if (buff[0] == 'p' && buff[1] == 'a' && buff[2] == '\n')
		return (ft_lstnew(1));
	if (buff[0] == 'p' && buff[1] == 'b' && buff[2] == '\n')
		return (ft_lstnew(2));
	if (buff[0] == 's' && buff[1] == 'a' && buff[2] == '\n')
		return (ft_lstnew(3));
	if (buff[0] == 's' && buff[1] == 'b' && buff[2] == '\n')
		return (ft_lstnew(4));
	if (buff[0] == 's' && buff[1] == 's' && buff[2] == '\n')
		return (ft_lstnew(5));
	if (buff[0] == 'r' && buff[1] == 'a' && buff[2] == '\n')
		return (ft_lstnew(6));
	if (buff[0] == 'r' && buff[1] == 'b' && buff[2] == '\n')
		return (ft_lstnew(7));
	if (buff[0] == 'r' && buff[1] == 'r' && buff[2] == '\n')
		return (ft_lstnew(8));
	if (buff[0] == 'r' && buff[1] == 'r' && buff[2] == 'a')
		return (ft_lstnew(9));
	if (buff[0] == 'r' && buff[1] == 'r' && buff[2] == 'b')
		return (ft_lstnew(10));
	if (buff[0] == 'r' && buff[1] == 'r' && buff[2] == 'r')
		return (ft_lstnew(11));
	else
		return (ft_lstnew(0));
}

void	exec_instruct(t_list **stack_a, t_list **stack_b, t_list *instruct)
{
	while (instruct)
	{
		if (instruct->content == 1)
			pa(stack_a, stack_b);
		else if (instruct->content == 2)
			pb(stack_a, stack_b);
		else if (instruct->content == 3)
			sa(stack_a);
		else if (instruct->content == 4)
			sb(stack_b);
		else if (instruct->content == 5)
			ss(stack_a, stack_b);
		else if (instruct->content == 6)
			ra(stack_a);
		else if (instruct->content == 7)
			rb(stack_b);
		else if (instruct->content == 8)
			rr(stack_a, stack_b);
		else if (instruct->content == 9)
			rra(stack_a);
		else if (instruct->content == 10)
			rrb(stack_b);
		else if (instruct->content == 11)
			rrr(stack_a, stack_b);
		instruct = instruct->next;
	}
}

int	check_instruct(t_list *instruct)
{
	while (instruct)
	{
		if (instruct->content == 0)
			return (0);
		instruct = instruct->next;
	}
	return (1);
}

int	check_sort(t_list *stack_a, t_list *stack_b)
{
	int	i;

	if (ft_lstsize(stack_b) > 0)
		return (0);
	while (stack_a->next != NULL)
	{
		i = stack_a->content;
		stack_a = stack_a->next;
		if (stack_a->content < i)
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_list	*stack_a;
	t_list	*stack_b;
	t_list	*instruct;
	char	buff[4];

	stack_b = NULL;
	if (argc > 1)
	{
		stack_a = create_stack(argc, argv);	
		while (1)
		{
			read(0, buff, 4);
			if (buff[0] == '\n')
				break;
			ft_lstadd_back(&instruct, list_instruct(buff));
		}
		if (!check_instruct(instruct))
		{
			write (0, "Error", 6);
			return (0);
		}
		exec_instruct(&stack_a, &stack_b, instruct);
		print_list(instruct);
		printf("\n");
		print_list(stack_a);
		printf("\n");
		print_list(stack_b);
		printf("\n");
		if (check_sort(stack_a, stack_b))
			write(1, "OK\n", 3);
		else
			write(1, "KO\n", 3);
	}
	return(0);
}
