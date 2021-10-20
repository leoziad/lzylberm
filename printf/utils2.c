/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 16:40:15 by lzylberm          #+#    #+#             */
/*   Updated: 2021/07/30 16:42:56 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	is_type(const char *fmt)
{
	return ((*fmt == 'c' || *fmt == 's' || *fmt == 'p'
			|| *fmt == 'd' || *fmt == 'i'
			|| *fmt == 'u' || *fmt == 'x' || *fmt == 'X' || *fmt == '%'));
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

size_t	ft_strlen(char *str)
{
	size_t	index;

	if (str == NULL)
		return (0);
	index = 0;
	while (str[index] != '\0')
		index++;
	return (index);
}

void	add_prefix(int *count)
{
	write(1, "0x", 2);
	*count += 2;
}
