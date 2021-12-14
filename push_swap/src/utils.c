/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:37:35 by lzylberm          #+#    #+#             */
/*   Updated: 2021/12/14 19:29:08 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

void	clear(t_list *stack)
{
	if (stack)
		ft_lstclear(&stack);
	write(0, "Error\n", 6);
	exit(0);
}

int	ft_atoi(const char *str, t_list **stack)
{
	int				index;
	int				sign;
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
	if ((sign == -1 && result > 2147483648)
		|| (sign == 1 && result > 2147483647) || !str[0] || str[index])
		clear(*stack);
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
				clear(*stack);
		}
		tmp1 = tmp1->next;
	}
}
