/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 10:23:27 by lzylberm          #+#    #+#             */
/*   Updated: 2021/04/20 15:53:44 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, unsigned int n)
{
	unsigned int	index;
	unsigned char	c_cpy;

	c_cpy = c;
	index = 0;
	while (index < n)
	{
		*(unsigned char *)dest = *(unsigned char *)src;
		if (*(unsigned char *)dest == c_cpy)
		{
			dest++;
			return (dest);
		}
		index++;
		dest++;
		src++;
	}
	return (NULL);
}
