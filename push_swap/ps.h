/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:34:54 by lzylberm          #+#    #+#             */
/*   Updated: 2021/11/24 19:40:21 by lzylberm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_H
# define PS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	int				content;
	int				i;
	int				pos;
	struct s_list	*next;
}					t_list;

char		*ft_strnew(size_t size);
t_list		*ft_lstnew(int content);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst);
int			ft_atoi(const char *str, t_list **stack);
void		ft_putchar(char c);
void		ft_putnbr(int nb);
void		ft_swap(int *a, int *b);
void		ft_sort_int_tab(int *tab, int size);
void		duplicates(t_list **stack);
void		sa(t_list **stack_a);
void		sb(t_list **stack_b);
void		ss(t_list **stack_a, t_list **stack_b);
void		pa(t_list **stack_a, t_list **stack_b);
void		pb(t_list **stack_a, t_list **stack_b);
void		ra(t_list **stack_a);
void		rb(t_list **stack_b);
void		rr(t_list **stack_a, t_list **stack_b);
void		rra(t_list **stack_a);
void		rrb(t_list **stack_b);
void		rrr(t_list **stack_a, t_list **stack_b);
void		sa_s(t_list **stack_a);
void		sb_s(t_list **stack_b);
void		ss_s(t_list **stack_a, t_list **stack_b);
void		pa_s(t_list **stack_a, t_list **stack_b);
void		pb_s(t_list **stack_a, t_list **stack_b);
void		ra_s(t_list **stack_a);
void		rb_s(t_list **stack_b);
void		rr_s(t_list **stack_a, t_list **stack_b);
void		rra_s(t_list **stack_a);
void		rrb_s(t_list **stack_b);
void		rrr_s(t_list **stack_a, t_list **stack_b);
int			indexing(int *index, int content);
void		create_index(t_list **stack);
void		update_pos(t_list **stack);
int			find_min(t_list **stack);
void		smart_rotate(t_list **stack, int i);
void		sort_3(t_list **stack_a);
void		sort_4(t_list **stack_a, t_list **stack_b);
void		sort_5(t_list **stack_a, t_list **stack_b);
void		chunk1_7(t_list **stack_a, t_list **stack_b, int size);
void		chunk2_7(t_list **stack_a, t_list **stack_b, int size);
void		chunk3_7(t_list **stack_a, t_list **stack_b, int size);
void		chunk4_7(t_list **stack_a, t_list **stack_b, int size);
void		chunk5_7(t_list **stack_a, t_list **stack_b, int size);
void		chunk6_7(t_list **stack_a, t_list **stack_b, int size);
void		chunk1_11(t_list **stack_a, t_list **stack_b, int size);
void		chunk2_11(t_list **stack_a, t_list **stack_b, int size);
void		chunk3_11(t_list **stack_a, t_list **stack_b, int size);
void		chunk4_11(t_list **stack_a, t_list **stack_b, int size);
void		chunk5_11(t_list **stack_a, t_list **stack_b, int size);
void		chunk6_11(t_list **stack_a, t_list **stack_b, int size);
void		chunk7_11(t_list **stack_a, t_list **stack_b, int size);
void		chunk8_11(t_list **stack_a, t_list **stack_b, int size);
void		chunk9_11(t_list **stack_a, t_list **stack_b, int size);
void		chunk10_11(t_list **stack_a, t_list **stack_b, int size);
void		chunk11_11(t_list **stack_a, t_list **stack_b, int size);
void		chunk12_11(t_list **stack_a, t_list **stack_b, int size);
void		push_chunks_7(t_list **stack_a, t_list **stack_b);
void		push_chunks_13(t_list **stack_a, t_list **stack_b);
void		push_back_chunks(t_list **stack_a, t_list **stack_b);
#endif
