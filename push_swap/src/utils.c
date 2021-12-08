/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:37:35 by lzylberm          #+#    #+#             */
/*   Updated: 2021/12/07 19:21:17 by lzylberm         ###   ########.fr       */
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
	{
		ft_lstclear(stack);
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
				ft_lstclear(stack);
				write(0, "Error\n", 6);
				exit(0);
			}
		}
		tmp1 = tmp1->next;
	}
}
