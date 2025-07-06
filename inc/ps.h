/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 16:30:13 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/06 17:56:51 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_H
# define PS_H

# include "libft.h"

# define NEWLINE() (write(1,"\n",1))


typedef struct s_ps
{
	t_list	*stack_a;
	t_list	*stack_b;
	int		size_a;
	int		size_b;
	int		total_size;
}				t_ps;

typedef void (*move)(t_ps *ps);

void	sa(t_ps *ps);
void	sb(t_ps *ps);
void	ss(t_ps *ps);
void	pa(t_ps *ps);
void	pb(t_ps *ps);
void	ra(t_ps *ps);
void	rb(t_ps *ps);
void	rr(t_ps *ps);
void	rra(t_ps *ps);
void	rrb(t_ps *ps);
void	rrr(t_ps *ps);

// UTILS
int		find_max_width(t_list *stack);
void    print_both_stacks(t_list *stack_a, t_list *stack_b);
void    print_stack(t_list *stack, char name);
int		count_stack_elements(t_list *stack);
void    ft_print_sub_banner(const char *title, const char *subtitle);

#endif