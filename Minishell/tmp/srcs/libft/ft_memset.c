/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:10:21 by lzylberm          #+#    #+#             */
/*   Updated: 2021/04/14 11:58:40 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memset(void *b, int c, unsigned int len)
{
	unsigned int	index;
	void			*ptr;

	index = 0;
	ptr = b;
	while (index < len)
	{
		*(unsigned char *)b = c;
		index++;
		b++;
	}
	return (ptr);
}
