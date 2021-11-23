/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:37:35 by lzylberm          #+#    #+#             */
/*   Updated: 2021/11/23 17:16:26 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc(sizeof(*str) * size + 1);
	if (str == NULL)
		return (NULL);
	while (i < size)
	{
		str[i] = '0';
		i++;
	}
	str[i] = '\0';
	return (str);
}

t_list	*ft_lstnew(int content)
{
	t_list		*new;

	new = malloc(sizeof(t_list));
	if (new != NULL)
	{
		new->content = content;
		new->next = NULL;
	}
	return (new);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	if (*lst == new)
		return ;
	new->next = *lst;
	*lst = new;
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list		*ptr;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	else
	{
		ptr = ft_lstlast(*lst);
		ptr->next = new;
	}
}


t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	ft_lstsize(t_list *lst)
{
	int		result;

	result = 0;
	while (lst)
	{
		result++;
		lst = lst->next;
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	int		index;
	int		sign;
	long long		result;

	index = 0;
	sign = 1;
	result = 0;
	if (str[index] == '-')
	{
		sign = -1;
		index++;
	}
	while (str[index] >= '0' && str[index] <= '9')
	{
		result = result * 10 + str[index] - 48;
		index++;
	}
	if ((sign == -1 && result > 2147483648) || (sign == 1 && result > 2147483647) || !str[0] || str[index])
	{
		write(0, "Error\n", 6);
		exit(0);
	}
	return ((int)result * sign);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	long int	lnb;

	lnb = nb;
	if (lnb < 0)
	{
		write(1, "-", 1);
		lnb = lnb * -1;
	}
	if (lnb > 9)
		ft_putnbr(lnb / 10);
	ft_putchar(48 + lnb % 10);
}

void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_sort_int_tab(int *tab, int size)
{
	int index_a;
	int index_b;

	index_a = 0;
	index_b = 1;
	while (index_a < size - 1)
	{
		while (index_b < size)
		{
			if (tab[index_a] > tab[index_b])
			{
				ft_swap(&tab[index_a], &tab[index_b]);
				index_b = index_a;

			}
			index_b++;
		}
		index_a++;
		index_b = index_a;
	}
}

void	duplicates(t_list **stack)
{
	t_list	*tmp1;
	t_list	*tmp2;

	tmp1 = *stack;
	while (tmp1->next != NULL)
	{
		tmp2 = tmp1;
		while (tmp2->next != NULL)
		{
			tmp2 = tmp2->next;
			if (tmp2->content == tmp1->content)
			{
				write(0, "Error\n", 6);
				exit(0);
			}
		}
		tmp1 = tmp1->next;
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

void	update_pos(t_list **stack)
{
	int		pos;
	t_list	*tmp;

	pos = 0;
	tmp = *stack;
	while (tmp)
	{
		tmp->pos = pos;
		pos++;
		tmp = tmp->next;
	}
}

int	find_min(t_list **stack)
{
	t_list	*tmp;

	tmp = *stack;
	while (tmp->i != 0)
		tmp = tmp->next;
	return (tmp->i);
}

void	smart_rotate(t_list **stack, int i)
{
	int		size;
	int		count;
	t_list	*tmp;

	size = ft_lstsize(*stack);
	tmp = *stack;
	while (tmp->i != i)
		tmp = tmp->next;
	count = size - tmp->pos;
	if (count > size / 2)
	{
		while (count < size)
		{
			ra(stack);
			count++;
		}
	}
	else
	{
		while (count > 0)
		{
			rra(stack);
			count--;
		}
	}
}

void	sort_3(t_list **stack_a)
{
	t_list	*stack;

	stack = *stack_a;
	if ((*stack).i > (*stack).next->i && (*stack).next->i > (*stack).next->next->i
			&& (*stack).next->next->i < (*stack).i)
	{
		sa(stack_a);
		rra(stack_a);
	}
	else if ((*stack).i > (*stack).next->i && (*stack).next->i < (*stack).next->next->i
			&& (*stack).next->next->i < (*stack).i)
		ra(stack_a);
	else if ((*stack).i > (*stack).next->i && (*stack).next->i < (*stack).next->next->i
			&& (*stack).next->next->i > (*stack).i)
		sa(stack_a);
	else if ((*stack).i < (*stack).next->i && (*stack).next->i > (*stack).next->next->i
			&& (*stack).next->next->i < (*stack).i)
		rra(stack_a);
	else if ((*stack).i < (*stack).next->i && (*stack).next->i > (*stack).next->next->i
			&& (*stack).next->next->i > (*stack).i)
	{
		sa(stack_a);
		ra(stack_a);
	}
}

void	sort_4(t_list **stack_a, t_list **stack_b)
{

	update_pos(stack_a);
	smart_rotate(stack_a, 0);
	pb(stack_a, stack_b);
	sort_3(stack_a);
	pa(stack_a, stack_b);
}

void	sort_5(t_list **stack_a, t_list **stack_b)
{
	update_pos(stack_a);
	smart_rotate(stack_a, 0);
	pb(stack_a, stack_b);
	update_pos(stack_a);
	smart_rotate(stack_a, 1);
	pb(stack_a, stack_b);
	sort_3(stack_a);
	pa(stack_a, stack_b);
	pa(stack_a, stack_b);
}

void	chunk1(t_list **stack_a, t_list **stack_b, int size)
{
	t_list	*tmp;

	update_pos(stack_a);
	tmp = *stack_a;
	while (tmp)
	{
		if (tmp->i < size / 5)
		{
			smart_rotate(stack_a, tmp->i);
			pb(stack_a, stack_b);
			update_pos(stack_a);
			tmp = *stack_a;
		}
		else
			tmp = tmp->next;
	}
}

void	chunk2(t_list **stack_a, t_list **stack_b, int size)
{
	t_list	*tmp;

	update_pos(stack_a);
	tmp = *stack_a;
	while (tmp)
	{
		if (tmp->i < (size / 5) * 2)
		{
			smart_rotate(stack_a, tmp->i);
			pb(stack_a, stack_b);
			update_pos(stack_a);
			tmp = *stack_a;
		}
		else
			tmp = tmp->next;
	}
}

void	chunk3(t_list **stack_a, t_list **stack_b, int size)
{
	t_list	*tmp;

	update_pos(stack_a);
	tmp = *stack_a;
	while (tmp)
	{
		if (tmp->i < (size / 5) * 3)
		{
			smart_rotate(stack_a, tmp->i);
			pb(stack_a, stack_b);
			update_pos(stack_a);
			tmp = *stack_a;
		}
		else
			tmp = tmp->next;
	}
}

void	chunk4(t_list **stack_a, t_list **stack_b, int size)
{
	t_list	*tmp;

	update_pos(stack_a);
	tmp = *stack_a;
	while (tmp)
	{
		if (tmp->i < (size / 5) * 4)
		{
			smart_rotate(stack_a, tmp->i);
			pb(stack_a, stack_b);
			update_pos(stack_a);
			tmp = *stack_a;
		}
		else
			tmp = tmp->next;
	}
}

void	push_chunks(t_list **stack_a, t_list **stack_b)
{
	int	size;

	size = ft_lstsize(*stack_a);
	chunk1(stack_a, stack_b, size);
	chunk2(stack_a, stack_b, size);
	chunk3(stack_a, stack_b, size);
	chunk4(stack_a, stack_b, size);
	while (*stack_a)
		pb(stack_a, stack_b);
}

void	push_back_chunks(t_list **stack_a, t_list **stack_b)
{
	int	size;

	size = ft_lstsize(*stack_b) - 1;
	update_pos(stack_b);
	while (size >= 0)
	{
		smart_rotate(stack_b, size);
		pa(stack_a, stack_b);
		update_pos(stack_b);
		size--;
	}
}
