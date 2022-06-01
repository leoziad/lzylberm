/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 10:37:00 by lzylberm          #+#    #+#             */
/*   Updated: 2021/04/24 15:47:38 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, unsigned int len)
{
	unsigned int	index;
	void			*ptr;

	index = 0;
	ptr = dst;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst == src)
		return (dst);
	if (src < dst)
	{
		src += len - 1;
		dst += len - 1;
		while (index < len && len != 0)
		{
			*(unsigned char *)dst = *(unsigned char *)src;
			dst--;
			src--;
			index++;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (ptr);
}
