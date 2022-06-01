/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:55:57 by lzylberm          #+#    #+#             */
/*   Updated: 2021/04/22 13:40:41 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	i_dest;
	unsigned int	i_src;
	unsigned int	total_lenght;
	unsigned int	dest_len;

	if (size == 0)
		return (ft_strlen(src));
	total_lenght = (ft_strlen(src) + ft_strlen(dest));
	i_dest = ft_strlen(dest);
	dest_len = i_dest;
	i_src = 0;
	while (src[i_src] != '\0' && i_dest < size - 1)
	{
		dest[i_dest] = src[i_src];
		i_src++;
		i_dest++;
	}
	dest[i_dest] = '\0';
	if (dest_len >= size)
		return (ft_strlen(src) + size);
	else
		return (total_lenght);
}
