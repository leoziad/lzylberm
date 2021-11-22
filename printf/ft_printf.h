/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:41:07 by lzylberm          #+#    #+#             */
/*   Updated: 2021/11/19 15:51:40 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

void	ft_putchar(char c);
void	putnbr(int nb, int *count);
void	putnbr_u(unsigned long long nb, int *count);
void	putnbr_b(unsigned long long nbr, char *base, int *count);
int		ft_printf(const char *fmt, ...);
int		ft_atoi(const char *str);
size_t	ft_strlen(char *str);
int		is_type(const char *fmt);
void	add_prefix(int *count);
#endif
