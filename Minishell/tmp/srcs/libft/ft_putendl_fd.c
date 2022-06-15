/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 17:17:58 by lzylberm          #+#    #+#             */
/*   Updated: 2021/04/24 15:48:05 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *str, int fd)
{
	if (str == NULL)
		return ;
	while (*str)
	{
		write(fd, &*str, 1);
		str++;
	}
	ft_putchar_fd('\n', fd);
}
