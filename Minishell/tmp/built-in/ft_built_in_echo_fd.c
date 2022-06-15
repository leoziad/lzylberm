/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_echo_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:49:13 by robin             #+#    #+#             */
/*   Updated: 2022/05/25 15:49:18 by robin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_built_in_echo_fd(char **str, int fd)
{
	int	i;
	int	y;

	str++;
	y = 0;
	i = ft_check_n(str);
	if (i > 0)
		y++;
	while (str[i])
	{
		ft_putstr_fd(str[i], fd);
		if (str[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (y == 0)
		ft_putchar_fd('\n', fd);
	exit_status = 0;
	return (0);
}