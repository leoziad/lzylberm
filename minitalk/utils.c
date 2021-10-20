/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 16:20:47 by lzylberm          #+#    #+#             */
/*   Updated: 2021/09/08 18:38:00 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	write(1, str, 1);
}

void	ft_putnbr(int nb)
{
	long int	lnb;

	lnb = nb;
	if (lnb < 0)
	{
		write(1, "-", 1);
		lnb = lnb * -1;
	}
	if (lnb > 9)
		ft_putnbr(lnb / 10);
	ft_putchar(48 + lnb % 10);
}

size_t	ft_strlen(char *str)
{
	size_t	index;

	index = 0;
	while (str[index] != '\0')
		index++;
	return (index);
}

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

void	ft_bzero(void *s, size_t n)
{
	size_t			index;
	unsigned char	*str;

	str = (unsigned char *)s;
	index = 0;
	while (index < n)
	{
		str[index] = 0;
		index++;
	}
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

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc(sizeof(*str) * size + 1);
	if (str == NULL)
		return (NULL);
	while (i < size)
	{
		str[i] = '0';
		i++;
	}
	str[i] = '\0';
	return (str);
}

t_list	*ft_lstnew(void *content)
{
	t_list		*new;

	new = malloc(sizeof(t_list));
	if (new != NULL)
	{
		new->content = content;
		new->next = NULL;
	}
	return (new);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list		*ptr;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	else
	{
		ptr = ft_lstlast(*lst);
		ptr->next = new;
	}
}

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (f == NULL)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst->content);
	free (lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list		*current;
	t_list		*tmp;

	if (del == NULL || lst == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		del(current->content);
		tmp = current->next;
		free (current);
		current = tmp;
	}
	(*lst) = NULL;
	lst = NULL;
}
