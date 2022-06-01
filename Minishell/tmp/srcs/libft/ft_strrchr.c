/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 11:38:41 by lzylberm          #+#    #+#             */
/*   Updated: 2021/04/24 16:17:14 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	int		count;
	char	c_cpy;

	c_cpy = (char)c;
	len = ft_strlen((char *)s);
	count = 0;
	while (*s)
		s++;
	while (count < len)
	{
		if (*s == c_cpy)
			return ((char *)s);
		s--;
		count++;
	}
	if (*s == c_cpy)
		return ((char *)s);
	return (NULL);
}
