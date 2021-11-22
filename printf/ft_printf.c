/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:01:32 by lzylberm          #+#    #+#             */
/*   Updated: 2021/11/22 22:34:26 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	read_type(const char *fmt)
{
	char	type;

	fmt++;
	if (is_type(fmt))
		type = *fmt;
	else
		type = 0;
	return (type);
}

void	print_s(va_list args, int *count)
{
	char	*str;
	int		len;

	str = va_arg(args, char *);
	len = ft_strlen(str);
	if (str)
	{
		write(1, str, len);
		*count += len;
	}
	else
	{
		write(1, "(null)", 6);
		*count += 6;
	}
}

void	global_print(va_list args, char type, int *count)
{
	if (type == 'c')
	{
		ft_putchar(va_arg(args, int));
		*count += 1;
	}
	else if (type == 's')
		print_s(args, count);
	else if (type == 'p')
	{
		add_prefix(count);
		putnbr_b(va_arg(args, unsigned long), "0123456789abcdef", count);
	}
	else if (type == 'd' || type == 'i')
		putnbr(va_arg(args, int), count);
	else if (type == 'u')
		putnbr_u(va_arg(args, unsigned int), count);
	else if (type == 'x')
		putnbr_b(va_arg(args, unsigned int), "0123456789abcdef", count);
	else if (type == 'X')
		putnbr_b(va_arg(args, unsigned int), "0123456789ABCDEF", count);
	else if (type == '%')
	{
		ft_putchar('%');
		*count += 1;
	}
}

void	print_basic(const char **fmt, int *count)
{
	while (**fmt != '\0' && **fmt != '%')
	{
		write(1, *fmt, 1);
		*fmt += 1;
		*count += 1;
	}
}

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	char	type;
	int		count;

	count = 0;
	va_start(args, fmt);
	while (*fmt != '\0')
	{
		print_basic(&fmt, &count);
		if (*fmt == '%')
			type = read_type(fmt);
		if (*fmt != '\0' && is_type(++fmt))
			fmt += 1;
		if (*fmt == '\0')
			break ;
		if (type != 0)
			global_print(args, type, &count);
	}
	if (is_type(--fmt) && *--fmt == '%')
		global_print(args, type, &count);
	va_end(args);
	return (count);
}
