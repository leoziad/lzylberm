/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 16:12:41 by lzylberm          #+#    #+#             */
/*   Updated: 2021/09/08 17:41:20 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstiter(t_list *lst, void (*f)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_putnbr(int nb);
size_t	ft_strlen(char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);
char	*ft_strdup(char *src);
void	ft_bzero(void *s, size_t n);
int		ft_atoi(const char *str);
char	*ft_strnew(size_t size);
#endif
