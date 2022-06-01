/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 11:50:27 by lzylberm          #+#    #+#             */
/*   Updated: 2021/04/24 16:41:21 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, unsigned int len)
{
	unsigned int		i_str;
	unsigned int		i_f;

	if (ft_strlen((char *)to_find) == 0)
		return ((char *)str);
	i_str = 0;
	i_f = 0;
	while (str[i_str] != '\0' && i_str < len)
	{
		while ((to_find[i_f] == str[i_str + i_f]) && (i_str + i_f) < len)
		{
			if (i_f == (unsigned int)ft_strlen((char *)to_find) - 1 || i_f == len)
				return ((char *)&str[i_str]);
			i_f++;
		}
		i_f = 0;
		i_str++;
	}
	return (0);
}
