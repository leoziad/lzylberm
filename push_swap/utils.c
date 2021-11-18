/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:37:35 by lzylberm          #+#    #+#             */
/*   Updated: 2021/11/18 15:56:39 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

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

int	ft_atoi(const char *str, char *error)
{
	int		index;
	int		sign;
	long long		result;

	index = 0;
	sign = 1;
	result = 0;
	if (str == NULL)
		return (0);
	if (str[index] == '-')
	{
		sign = -1;
		index++;
	}
	while (str[index] != '\0')
	{
		if (str[index] < '0' || str[index] > '9')
			*error = 1;
		result = result * 10 + str[index] - 48;
		index++;
	}
	if ((sign == -1 && result > 2147483648) || (sign == 1 && result > 2147483647))
		*error = 1;
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

void	duplicates(t_list **stack, char *error)
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
				*error = 1;
				return ;
			}
		}
		tmp1 = tmp1->next;
	}
}
