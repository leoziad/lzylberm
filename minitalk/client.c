/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 16:33:38 by lzylberm          #+#    #+#             */
/*   Updated: 2021/10/21 15:00:39 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*char_to_bin(char c)
{
	char	*bin_val;
	int		index;

	index = 0;
	bin_val = ft_strnew(8);
	if (c % 2 != 0)
		bin_val[index] = '1';
	index++;
	while (c > 1)
	{
		c = c / 2;
		if (c % 2 != 0)
			bin_val[index] = '1';
		index++;
	}
	return (bin_val);
}

void	bin_sig(char *bin, int serv_pid)
{
	int		i_bin;

	i_bin = 0;
	while (i_bin < 8)
	{
		if (bin[i_bin] == '0')
			kill(serv_pid, SIGUSR1);
		else
			kill(serv_pid, SIGUSR2);
		i_bin++;
		usleep(65);
	}
}

int	main(int argc, char **argv)
{
	char	*bin;
	int		i_str;
	int		serv_pid;

	bin = NULL;
	if (argc == 3)
	{
		serv_pid = ft_atoi(argv[1]);
		i_str = 0;
		while (argv[2][i_str])
		{
			bin = char_to_bin(argv[2][i_str]);
			bin_sig(bin, serv_pid);
			i_str++;
			free (bin);
		}
	}
	return (0);
}
