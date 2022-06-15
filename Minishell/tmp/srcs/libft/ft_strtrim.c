/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:27:02 by lzylberm          #+#    #+#             */
/*   Updated: 2021/04/24 16:23:55 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_set(char const *str, char const *charset)
{
	while (*charset)
	{
		if (*str == *charset++)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char const		*ptr;
	int				index;
	int				start;
	int				end;

	if (s1 == NULL)
		return (NULL);
	ptr = s1;
	index = 0;
	while (ft_check_set(s1, set))
	{
		s1++;
		index++;
	}
	start = index;
	while (*s1 != '\0')
	{
		s1++;
		index++;
	}
	s1--;
	index--;
	while (ft_check_set(s1, set))
	{
		s1--;
		index--;
	}
	end = index + 1;
	return (ft_substr(ptr, start, (end - start)));
}
