/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 16:11:41 by lzylberm          #+#    #+#             */
/*   Updated: 2021/11/22 20:13:04 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_bin	g_bin_val;

void	handle_sigusr1(int signum)
{
	(void)signum;
	g_bin_val.val[g_bin_val.count] = '0';
	g_bin_val.count++;
	if (g_bin_val.count == 8)
	{
		bin_to_char(g_bin_val.val);
		g_bin_val.count = 0;
	}
}

void	handle_sigusr2(int signum)
{
	(void)signum;
	g_bin_val.val[g_bin_val.count] = '1';
	g_bin_val.count++;
	if (g_bin_val.count == 8)
	{
		bin_to_char(g_bin_val.val);
		g_bin_val.count = 0;
	}
}

void	bin_to_char(char *bin_val)
{
	char	c;
	int		count;

	c = 0;
	count = 0;
	while (count < 8)
	{
		if (count == 0 && bin_val[count] == '1')
			c += 1;
		else if (count > 0 && bin_val[count] == '1')
			c += ft_recursive_power(2, count);
		count++;
	}
	ft_putchar(c);
}

int	main(void)
{
	int					pid;
	struct sigaction	sa1;
	struct sigaction	sa2;

	sigemptyset(&sa1.sa_mask);
	sigaddset(&sa1.sa_mask, SIGUSR1);
	sigemptyset(&sa2.sa_mask);
	sigaddset(&sa2.sa_mask, SIGUSR2);
	sa1.sa_handler = &handle_sigusr1;
	sa2.sa_handler = &handle_sigusr2;
	sigaction(SIGUSR1, &sa1, NULL);
	sigaction(SIGUSR2, &sa2, NULL);
	pid = getpid();
	write(1, "Server's PID is : ", sizeof(char) * 18);
	ft_putnbr(pid);
	write(1, "\n", 1);
	g_bin_val.val = malloc(sizeof(char) * 8);
	g_bin_val.count = 0;
	while (1)
		pause();
}
