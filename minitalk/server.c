/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 16:11:41 by lzylberm          #+#    #+#             */
/*   Updated: 2021/09/08 18:38:21 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*bin_val;

void	handle_sigusr1(int signum)
{
	(void)signum;
	*bin_val = '0';
	bin_val++;
}

void	handle_sigusr2(int signum)
{
	(void)signum;
	*bin_val = '1';
	bin_val++;
}

void	bin_to_char(char *bin_val)
{
	char	c;
	int		count;

	c = 0;
	count = 0;
	while (count < 8)
	{
		if (count == 0 && *bin_val == '1')
			c += 1;
		else if (count == 1 && *bin_val == '1')
			c += 2;
		else if (count == 2 && *bin_val == '1')
			c += 4;
		else if (count == 3 && *bin_val == '1')
			c += 8;
		else if (count == 4 && *bin_val == '1')
			c += 16;
		else if (count == 5 && *bin_val == '1')
			c += 32;
		else if (count == 6 && *bin_val == '1')
			c += 64;
		else if (count == 7 && *bin_val == '1')
			c += 128;
		bin_val++;
	}
	bin_val -= 8;
	ft_putchar(c);
}

int		check_last(t_list *str)
{
	t_list	*last;

	last = ft_lstlast(str);
	if (last->content == '\0')
		return (1);
	else
		return (0);
}


int	main(void)
{
	int	pid;
	int	count;
	t_list	*str;
	struct sigaction sa1;
	struct sigaction sa2;

	sigemptyset(&sa1.sa_mask);
	sigaddset(&sa1.sa_mask, SIGUSR1);
	sigemptyset(&sa2.sa_mask);
	sigaddset(&sa2.sa_mask, SIGUSR2);
	sa1.sa_handler = &handle_sigusr1;
	sa2.sa_handler = &handle_sigusr2;
	sigaction(SIGUSR1, &sa1, NULL);
	sigaction(SIGUSR2, &sa2, NULL);

	str = NULL;
	pid = getpid();
	write(1, "Server's PID is : ", sizeof(char) * 18);
	ft_putnbr(pid);
	write(1, "\n", 1);
	bin_val = malloc(sizeof(char) * 8);
	while(1)
	{
		count = 0;
		while (count < 8)
		{
			pause();
			count++;
		}
		bin_val -= 8;
		bin_to_char(bin_val);
		pause();
	}
}
