/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 14:03:24 by lzylberm          #+#    #+#             */
/*   Updated: 2021/07/30 16:09:18 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static int	ft_isspace(char c)
{
	if (c == 32 || c == '\n' || c == 9 || c == '\v' || c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int						index;
	int						sign;
	unsigned long long		result;

	index = 0;
	sign = 1;
	result = 0;
	if (str == NULL)
		return (0);
	while (str[index] != '\0' && ft_isspace(str[index]))
		index++;
	if (str[index] != '\0' && (str[index] == '-' || str[index] == '+'))
	{
		if (str[index] == '-')
			sign = -1;
		index++;
	}
	while (str[index] != '\0' && (str[index] >= '0' && str[index] <= '9'))
	{
		result = result * 10 + str[index] - 48;
		index++;
	}
	return ((int)result * sign);
}

void	putnbr(int nb, int *count)
{
	long int	lnb;

	lnb = nb;
	if (lnb < 0)
	{
		ft_putchar('-');
		*count += 1;
		lnb = lnb * -1;
	}
	if (lnb > 9)
		putnbr(lnb / 10, count);
	ft_putchar(48 + lnb % 10);
	*count += 1;
}

void	putnbr_u(unsigned long long nb, int *count)
{
	unsigned long long	lnb;

	lnb = nb;
	if (lnb > 9)
		putnbr_u(lnb / 10, count);
	ft_putchar(48 + lnb % 10);
	*count += 1;
}

void	putnbr_b(unsigned long long nbr, char *base, int *count)
{
	unsigned long long	base_len;
	int					index;

	index = 0;
	base_len = ft_strlen(base);
	index = 0;
	if (nbr >= base_len)
		putnbr_b(nbr / base_len, base, count);
	ft_putchar(base[nbr % base_len]);
	*count += 1;
}
