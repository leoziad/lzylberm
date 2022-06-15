/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:49:37 by lzylberm          #+#    #+#             */
/*   Updated: 2021/04/24 15:31:36 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(char c)
{
	if (c == 32 || c == '\n' || c == 9 || c == '\v' || c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

static int	ft_sign(char *str)
{
	int		sign;

	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		sign = 1;
	else if (*str == '-')
		sign = -1;
	else if (*str >= '0' && *str <= '9')
		return (1);
	str++;
	if (*str == '+' || *str == '-')
		return (0);
	else
		return (sign);
}

int	ft_atoi(char *str)
{
	int		index;
	int		result;

	index = 0;
	result = 0;
	while (ft_isspace(str[index]))
		index++;
	while (str[index] == '-' || str[index] == '+')
	{
		index++;
	}
	while (str[index] >= '0' && str[index] <= '9')
	{
		result = result * 10 + str[index] - 48;
		index++;
	}
	return (result * ft_sign(str));
}
