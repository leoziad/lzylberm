/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 16:20:47 by lzylberm          #+#    #+#             */
/*   Updated: 2021/10/21 14:38:36 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	index;

	if (dest == NULL || src == NULL)
		return (0);
	if (dstsize > 0)
	{
		index = 0;
		while (src[index] != '\0' && index < dstsize - 1)
		{
			dest[index] = src[index];
			index++;
		}
		dest[index] = '\0';
	}
	return (ft_strlen((char *)src));
}

char	*ft_strdup(char *src)
{
	char	*ptr;

	if (src == NULL)
		return (NULL);
	ptr = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, src, (ft_strlen(src) + 1));
	return (ptr);
}

static int	ft_isspace(char c)
{
	if (c == 32 || c == '\n' || c == 9 || c == '\v' || c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

static int	ft_flow(const char *str, int index, int sign)
{
	int	count;

	count = 0;
	while (str[index] != '\0' && (str[index] >= '0' && str[index] <= '9'))
	{
		count++;
		index++;
	}
	if (count > 19 && sign == 1)
		return (-1);
	if (count > 19 && sign == -1)
		return (0);
	if (count == 19 && str[index - 1] > '6' && sign == 1)
		return (-1);
	if (count == 19 && str[index - 1] > '7' && sign == -1)
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	int						index;
	int						sign;
	unsigned long long		result;

	index = 0;
	sign = 1;
	result = 0;
	if (str == NULL)
		return (0);
	while (str[index] != '\0' && ft_isspace(str[index]))
		index++;
	if (str[index] != '\0' && (str[index] == '-' || str[index] == '+'))
	{
		if (str[index] == '-')
			sign = -1;
		index++;
	}
	if (ft_flow(str, index, sign) == 0 || ft_flow(str, index, sign) == -1)
		return (ft_flow(str, index, sign));
	while (str[index] != '\0' && (str[index] >= '0' && str[index] <= '9'))
	{
		result = result * 10 + str[index] - 48;
		index++;
	}
	return ((int)result * sign);
}
