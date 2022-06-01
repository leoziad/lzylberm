/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 17:22:06 by lzylberm          #+#    #+#             */
/*   Updated: 2021/04/24 15:41:53 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_card(long long int n)
{
	int		result;

	result = 0;
	while (n > 9)
	{
		n /= 10;
		result++;
	}
	return (result + 1);
}

static void	ft_revstr(char *str, int size)
{
	int	index;
	int	rev_index;
	int	tmp;

	index = 0;
	rev_index = size - 1;
	while (index < rev_index)
	{
		tmp = str[index];
		str[index] = str[rev_index];
		str[rev_index] = tmp;
		index++;
		rev_index--;
	}
}

static char	*ft_convert(long long int n, int index, char *str)
{
	if (n > 9)
		ft_convert(n / 10, index + 1, str);
	str[index] = (n % 10) + 48;
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str;
	long long int	nb;

	if (n < 0)
	{
		nb = (long long int)n * -1;
		str = ft_strnew(ft_card(nb) + 1);
		if (str == NULL)
			return (NULL);
		str[ft_card(nb)] = '-';
		ft_revstr(ft_convert(nb, 0, str), ft_strlen(str));
		return (str);
	}
	else
	{
		str = ft_strnew(ft_card(n));
		if (str == NULL)
			return (NULL);
		ft_revstr(ft_convert(n, 0, str), ft_strlen(str));
		return (str);
	}
}
