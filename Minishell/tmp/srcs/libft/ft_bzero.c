/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:52:11 by lzylberm          #+#    #+#             */
/*   Updated: 2021/04/01 16:14:59 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_bzero(void *s, unsigned int n)
{
	unsigned int	index;

	index = 0;
	while (index < n)
	{
		*(unsigned char *)s = 0;
		index++;
		s++;
	}
	return (s);
}
