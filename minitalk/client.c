/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 16:33:38 by lzylberm          #+#    #+#             */
/*   Updated: 2021/09/08 18:38:24 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*t_list	*char_to_bin(char c)
{
	t_list	*bin_val;
	int	count;
	
	count = 1;
	if (c % 2 == 0)
		bin_val = ft_lstnew("0");
	else
		bin_val = ft_lstnew("1");
	while (c > 1)
	{
		c = c / 2;
		if (c % 2 == 0)
		{
			ft_lstadd_back(&bin_val, ft_lstnew("0"));
			count++;
		}
		else
		{
			ft_lstadd_back(&bin_val, ft_lstnew("1"));
			count++;
		}
	}
	while (count < 8)
	{
		ft_lstadd_back(&bin_val, ft_lstnew("0"));
		count++;
	}
	return (bin_val);
}*/

char	*char_to_bin(char c)
{
	char	*bin_val;
	int		index;

	index = 0;
	bin_val = ft_strnew(8);
	if (c % 2 != 0)
		bin_val[index] = '1';
	index++;
	while(c > 1)
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
				usleep(10);
			}
			i_str++;
		}
	}
	free (bin);
	return (0);
}
