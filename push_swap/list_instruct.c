/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_instruct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:19:19 by lzylberm          #+#    #+#             */
/*   Updated: 2021/11/26 11:28:05 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

t_list	*list_instruct_p(char *line, t_list **stack_a)
{
	if (line[1] == 'a' && line[2] == '\0')
		return (ft_lstnew(1));
	if (line[1] == 'b' && line[2] == '\0')
		return (ft_lstnew(2));
	else
	{
		ft_lstclear(stack_a);
		write(0, "Error\n", 6);
		exit(0);
	}
}

t_list	*list_instruct_s(char *line, t_list **stack_a)
{
	if (line[1] == 'a' && line[2] == '\0')
		return (ft_lstnew(3));
	if (line[1] == 'b' && line[2] == '\0')
		return (ft_lstnew(4));
	if (line[1] == 's' && line[2] == '\0')
		return (ft_lstnew(5));
	else
	{
		ft_lstclear(stack_a);
		write(0, "Error\n", 6);
		exit(0);
	}
}

t_list	*list_instruct_r(char *line, t_list **stack_a)
{
	if (line[1] == 'a' && line[2] == '\0')
		return (ft_lstnew(6));
	if (line[1] == 'b' && line[2] == '\0')
		return (ft_lstnew(7));
	if (line[1] == 'r' && line[2] == '\0')
		return (ft_lstnew(8));
	if (line[1] == 'r' && line[2] == 'a' && line[3] == '\0')
		return (ft_lstnew(9));
	if (line[1] == 'r' && line[2] == 'b' && line[3] == '\0')
		return (ft_lstnew(10));
	if (line[1] == 'r' && line[2] == 'r' && line[3] == '\0')
		return (ft_lstnew(11));
	else
	{
		ft_lstclear(stack_a);
		write(0, "Error\n", 6);
		exit(0);
	}
}

void	exec_instruct_2(t_list **stack_a, t_list **stack_b, t_list *instruct)
{
	if (instruct->content == 7)
		rb_s(stack_b);
	else if (instruct->content == 8)
		rr_s(stack_a, stack_b);
	else if (instruct->content == 9)
		rra_s(stack_a);
	else if (instruct->content == 10)
		rrb_s(stack_b);
	else if (instruct->content == 11)
		rrr_s(stack_a, stack_b);
}
