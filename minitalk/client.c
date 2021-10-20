/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 16:33:38 by lzylberm          #+#    #+#             */
/*   Updated: 2021/10/20 18:42:37 by lzylberm         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	char	*str;
	char	*bin;
	int		i_str;
	int		i_bin;
	int		serv_pid;

	bin = NULL;
	if (argc == 3)
	{
		str = ft_strdup(argv[2]);
		serv_pid = ft_atoi(argv[1]);
		i_str = 0;
		if (str == NULL)
			return (0);
		while (str[i_str])
		{
			i_bin = 0;
			bin = char_to_bin(str[i_str]);
			while (i_bin < 8)
			{
				if (bin[i_bin] == '0')
					kill(serv_pid, SIGUSR1);
				else
					kill(serv_pid, SIGUSR2);
				i_bin++;
				usleep(65);
			}
			i_str++;
		}
	}
	free (bin);
	return (0);
}
