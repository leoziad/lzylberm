/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:49:42 by lzylberm          #+#    #+#             */
/*   Updated: 2021/04/16 14:37:16 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(int size)
{
	int		index;
	char	*result;

	index = 0;
	result = malloc(sizeof(char) * size + 1);
	if (result == NULL)
		return (NULL);
	while (index <= size)
	{
		result[index] = '\0';
		index++;
	}
	return (result);
}
