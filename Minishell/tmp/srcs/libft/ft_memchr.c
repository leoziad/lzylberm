/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 10:59:46 by lzylberm          #+#    #+#             */
/*   Updated: 2021/04/24 15:46:18 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, unsigned int n)
{
	unsigned int	index;
	unsigned char	c_cpy;

	c_cpy = (unsigned char)c;
	index = 0;
	if (n > 0)
	{
		while (index < n)
		{
			if (*(unsigned char *)s == c_cpy)
				return ((unsigned char *)s);
			s++;
			index++;
		}
		if (*(unsigned char *)s == '\0' && c_cpy == '\0')
			return ((unsigned char *)s);
	}
	return (NULL);
}
