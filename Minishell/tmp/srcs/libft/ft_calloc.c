/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:07:47 by lzylberm          #+#    #+#             */
/*   Updated: 2021/04/14 13:26:16 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(unsigned int count, unsigned int size)
{
	void			*ptr;
	void			*ptr_cpy;
	unsigned int	index;

	index = 0;
	ptr = malloc(count * size);
	ptr_cpy = ptr;
	if (ptr != NULL)
	{
		while (index < (count * size))
		{
			*(unsigned int *)ptr = 0;
			index++;
			ptr++;
		}
	}
	return (ptr_cpy);
}
