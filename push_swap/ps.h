/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzylberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:34:54 by lzylberm          #+#    #+#             */
/*   Updated: 2021/12/07 12:32:46 by lzylberm         ###   ########.fr       */
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
t_list		*list_instruct_p(char *buff, t_list **stack_a);
t_list		*list_instruct_s(char *buff, t_list **stack_a);
t_list		*list_instruct_r(char *buff, t_list **stack_a);
void		exec_instruct_2(t_list **stack_a, t_list **stack_b,
				t_list *instruct);
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
void		smart_rotate(t_list **stack, int i);
void		sort_3(t_list **stack_a);
void		sort_4(t_list **stack_a, t_list **stack_b);
void		sort_5(t_list **stack_a, t_list **stack_b);
void		chunk1_6(t_list **stack_a, t_list **stack_b, int size);
void		chunk2_6(t_list **stack_a, t_list **stack_b, int size);
void		chunk3_6(t_list **stack_a, t_list **stack_b, int size);
void		chunk4_6(t_list **stack_a, t_list **stack_b, int size);
void		chunk5_6(t_list **stack_a, t_list **stack_b, int size);
void		chunk1_13(t_list **stack_a, t_list **stack_b, int size);
void		chunk2_13(t_list **stack_a, t_list **stack_b, int size);
void		chunk3_13(t_list **stack_a, t_list **stack_b, int size);
void		chunk4_13(t_list **stack_a, t_list **stack_b, int size);
void		chunk5_13(t_list **stack_a, t_list **stack_b, int size);
void		chunk6_13(t_list **stack_a, t_list **stack_b, int size);
void		chunk7_13(t_list **stack_a, t_list **stack_b, int size);
void		chunk8_13(t_list **stack_a, t_list **stack_b, int size);
void		chunk9_13(t_list **stack_a, t_list **stack_b, int size);
void		chunk10_13(t_list **stack_a, t_list **stack_b, int size);
void		chunk11_13(t_list **stack_a, t_list **stack_b, int size);
void		chunk12_13(t_list **stack_a, t_list **stack_b, int size);
void		push_chunks_6(t_list **stack_a, t_list **stack_b);
void		push_chunks_13(t_list **stack_a, t_list **stack_b);
void		push_back_chunks(t_list **stack_a, t_list **stack_b);
int			get_next_line(int fd, char **line);
#endif
