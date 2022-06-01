/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:24:26 by lzylberm          #+#    #+#             */
/*   Updated: 2021/04/16 12:01:03 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int	index;
	int				src_len;

	if (dest == NULL || src == NULL)
		return (0);
	src_len = 0;
	index = 0;
	while (src[src_len] != '\0')
		src_len++;
	while (src[index] != '\0' && index < size - 1)
	{
		if (index < size - 1 && size > 0)
			dest[index] = src[index];
		index++;
	}
	if (size > 0)
		dest[index] = '\0';
	return (src_len);
}
