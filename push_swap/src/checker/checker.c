/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:46:17 by lzylberm          #+#    #+#             */
/*   Updated: 2021/12/07 19:40:02 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

t_list	*create_stack(int argc, char **argv)
{
	t_list	*stack;
	int		i;

	i = 2;
	stack = ft_lstnew(ft_atoi(argv[1], &stack));
	while (i < argc)
	{
		ft_lstadd_back(&stack, ft_lstnew(ft_atoi(argv[i], &stack)));
		i++;
	}
	duplicates(&stack);
	return (stack);
}

t_list	*list_instruct(char *line, t_list **stack_a)
{
	if (line[0] == 'p')
		return (list_instruct_p(line, stack_a));
	if (line[0] == 's')
		return (list_instruct_s(line, stack_a));
	if (line[0] == 'r')
		return (list_instruct_r(line, stack_a));
	else
	{
		ft_lstclear(stack_a);
		write(0, "Error\n", 6);
		exit(0);
	}
}

void	exec_instruct(t_list **stack_a, t_list **stack_b, t_list *instruct)
{
	while (instruct)
	{
		if (instruct->content == 1)
			pa_s(stack_a, stack_b);
		else if (instruct->content == 2)
			pb_s(stack_a, stack_b);
		else if (instruct->content == 3)
			sa_s(stack_a);
		else if (instruct->content == 4)
			sb_s(stack_b);
		else if (instruct->content == 5)
			ss_s(stack_a, stack_b);
		else if (instruct->content == 6)
			ra_s(stack_a);
		else if (instruct->content > 6)
			exec_instruct_2(stack_a, stack_b, instruct);
		instruct = instruct->next;
	}
}

void	check_sort(t_list *stack_a, t_list *stack_b)
{
	int	i;

	if (ft_lstsize(stack_b) > 0)
	{
		write (1, "KO\n", 3);
		return ;
	}
	while (stack_a->next != NULL)
	{
		i = stack_a->content;
		stack_a = stack_a->next;
		if (stack_a->content < i)
		{
			write (1, "KO\n", 3);
			return ;
		}
	}
	write(1, "OK\n", 3);
}

int	main(int argc, char **argv)
{
	t_list	*stack_a;
	t_list	*stack_b;
	t_list	*instruct;
	char	*line;

	if (argc > 1)
	{
		stack_a = create_stack(argc, argv);
		while (get_next_line(0, &line))
		{
			if (line[0] == '\0')
				break ;
			ft_lstadd_back(&instruct, list_instruct(line, &stack_a));
		}
		exec_instruct(&stack_a, &stack_b, instruct);
		check_sort(stack_a, stack_b);
	}
	ft_lstclear(&stack_a);
	ft_lstclear(&stack_b);
	return (0);
}
