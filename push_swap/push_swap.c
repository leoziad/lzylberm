/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:34:00 by lzylberm          #+#    #+#             */
/*   Updated: 2021/11/18 16:44:43 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

void	print_list(t_list *lst)
{
	while(lst)
	{
		ft_putnbr(lst->i);
		write(1, " ", 1);
		lst = lst->next;
	}
}

int	indexing(int *index, int content)
{
	int	i;

	i = 0;
	while (index[i] != content)
		i++;
	return (i);
}

void	create_index(t_list **stack)
{
	int	index[ft_lstsize(*stack)];
	int	i;
	t_list	*tmp;

	tmp = *stack;
	i = 0;
	while (tmp->next != NULL)
	{
		index[i] = tmp->content;
		i++;
		tmp = tmp->next;
	}
	index[i] = tmp->content;
	ft_sort_int_tab(index, i + 1);
	i = 0;
	tmp = *stack;
	while (tmp->next != NULL)
	{
		tmp->i = indexing(index, tmp->content);
		tmp = tmp->next;
	}
	tmp->i = indexing(index, tmp->content);
}

int	find_loop_up(t_list **stack)
{
	int		low;
	int		max;
	int		count;
	t_list	*tmp1;
	t_list	*tmp2;

	tmp1 = *stack;
	count = 0;
	max = 0;
	low = tmp1->i;
	while (tmp1->next != NULL)
	{
		tmp2 = tmp1->next;
		while ((tmp2->next != NULL) && (tmp2->i == tmp1->i + count + 1))
		{
			count++;
			tmp2 = tmp2->next;
			if (tmp2->next == NULL && (tmp2->i == tmp1->i + count + 1))
				count++;
		}
		if (count > max)
		{
			low = tmp1->i;
			max = count;
		}
		while (count > 0)
		{
			tmp1 = tmp1->next;
			count--;
		}
		if (tmp1->next != NULL)
			tmp1 = tmp1->next;
	}
	return (low);
}

int	find_loop_down(t_list **stack)
{
	int		high;
	int		max;
	int		count;
	t_list	*tmp1;
	t_list	*tmp2;

	tmp1 = *stack;
	count = 0;
	max = 0;
	high = tmp1->i;
	while (tmp1->next != NULL)
	{
		tmp2 = tmp1->next;
		while ((tmp2->next != NULL) && (tmp2->i == tmp1->i - count - 1))
		{
			count++;
			tmp2 = tmp2->next;
			if (tmp2->next == NULL && (tmp2->i == tmp1->i - count - 1))
				count++;
		}
		if (count > max)
		{
			high = tmp1->i;
			max = count;
		}
		while (count > 0)
		{
			tmp1 = tmp1->next;
			count--;
		}
		if (tmp1->next != NULL)
			tmp1 = tmp1->next;
	}
	return (high);
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
		write(2, "Error\n", 6);

	create_index(&stack_a);
	print_list(stack_a);
	printf("\n");
	printf("biggest loop up starts at %d\n", find_loop_up(&stack_a));
	printf("biggest loop down starts at %d\n", find_loop_down(&stack_a));
	
	return (0);
}
