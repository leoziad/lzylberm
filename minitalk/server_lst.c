/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 16:11:41 by lzylberm          #+#    #+#             */
/*   Updated: 2021/09/08 18:02:04 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_list	*bin_str;

void	handle_sigusr1(int signum)
{
	(void)signum;
	ft_lstadd_back(&bin_str, ft_lstnew("0"));
}

void	handle_sigusr2(int signum)
{
	(void)signum;
	ft_lstadd_back(&bin_str, ft_lstnew("1"));
}

void	bin_to_char(t_list *bin_str, t_list *str)
{
	char	*c;
	int		count;

	c = ft_strnew(1);
	c[0] = 0;
	count = 0;
	while (bin_str->next != NULL)
	{
		if (count == 0 && bin_str->content[0] == '1')
			c[0] += 1;
		else if (count == 1 && bin_str->content[0] == '1')
			c[0] += 2;
		else if (count == 2 && bin_str->content[0] == '1')
			c[0] += 4;
		else if (count == 3 && bin_str->content[0] == '1')
			c[0] += 8;
		else if (count == 4 && bin_str->content[0] == '1')
			c[0] += 16;
		else if (count == 5 && bin_str->content[0] == '1')
			c[0] += 32;
		else if (count == 6 && bin_str->content[0] == '1')
			c[0] += 64;
		else if (count == 7 && bin_str->content[0] == '1')
			c[0] += 128;
		count ++;
		bin_str = bin_str->next;
	}
	ft_lstadd_back(&str, ft_lstnew(c));
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
	bin_str = ft_lstnew("s");
	while(check_last(str) != 1)
	{
		count = 0;
		while (count < 8)
		{
			pause();
			count++;
		}
		bin_str = bin_str->next;
		bin_to_char(bin_str, str);
	}
	ft_lstiter(str, &ft_putstr);
	pause();
}
