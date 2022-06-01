/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:55:40 by lzylberm          #+#    #+#             */
/*   Updated: 2021/04/24 15:46:50 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, unsigned int n)
{
	unsigned int	index;
	void			*ptr;

	index = 0;
	ptr = dest;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (index < n)
	{
		*(unsigned char *)dest = *(unsigned char *)src;
		index++;
		dest++;
		src++;
	}
	return (ptr);
}
