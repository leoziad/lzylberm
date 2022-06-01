/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:23:11 by lzylberm          #+#    #+#             */
/*   Updated: 2021/04/24 16:26:11 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, unsigned int len)
{
	unsigned int		index;
	char				*ptr;
	char				*substr;

	if (s == NULL)
		return (NULL);
	else if (start > (unsigned int)ft_strlen((char *)s))
	{
		ptr = malloc(1);
		*ptr = '\0';
		return (ptr);
	}
	else if (len > ((unsigned int)ft_strlen((char *)s) - start))
	{
		ptr = ft_strnew(((unsigned int)ft_strlen((char *)s) - start));
		if (ptr == NULL)
			return (NULL);
	}
	else
	{
		ptr = ft_strnew(len);
		if (ptr == NULL)
			return (NULL);
	}
	substr = ptr;
	index = start;
	while (s[index] && index < (start + len))
	{
		*ptr = s[index];
		ptr++;
		index++;
	}
	return (substr);
}
