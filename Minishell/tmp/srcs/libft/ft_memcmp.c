/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 11:29:38 by lzylberm          #+#    #+#             */
/*   Updated: 2021/04/24 15:46:34 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_memcmp(const void *s1, const void *s2, unsigned int n)
{
	unsigned int	index;

	index = 0;
	while (*(unsigned char *)s1 == *(unsigned char *)s2 && index < n)
	{
		if (index == n - 1)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
		index++;
	}
	if (index == n)
		return (0);
	else
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
