/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 09:55:07 by lzylberm          #+#    #+#             */
/*   Updated: 2021/04/24 16:11:19 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		index;

	if (s == NULL)
		return (NULL);
	str = ft_strnew(ft_strlen((char *)s));
	if (str == NULL)
		return (NULL);
	index = 0;
	while (s[index] != '\0')
	{
		str[index] = f(index, s[index]);
		index++;
	}
	return (str);
}
