/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:53:24 by lzylberm          #+#    #+#             */
/*   Updated: 2021/11/26 18:45:49 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_sort_int_tab(int *tab, int size)
{
	int	index_a;
	int	index_b;

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
	int		*index;
	int		i;
	t_list	*tmp;

	index = malloc(sizeof(int) * ft_lstsize(*stack));
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
	free(index);
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
