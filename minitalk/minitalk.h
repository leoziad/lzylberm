/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 16:12:41 by lzylberm          #+#    #+#             */
/*   Updated: 2021/11/22 19:37:38 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>

typedef struct bin_val
{
	char	*val;
	int		count;
}			t_bin;

void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_putnbr(int nb);
size_t	ft_strlen(char *str);
void	bin_to_char(char *bin_val);
int		ft_recursive_power(int nb, int power);
#endif
