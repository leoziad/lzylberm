/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 13:45:40 by lzylberm          #+#    #+#             */
/*   Updated: 2021/04/24 16:01:23 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	c_cpy;

	c_cpy = (char)c;
	while (*s)
	{
		if (*s == c_cpy)
			return ((char *)s);
		s++;
	}
	if (*s == c_cpy)
		return ((char *)s);
	return (NULL);
}
