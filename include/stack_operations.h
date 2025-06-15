/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:17:36 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:17:37 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_OPERATIONS_H
# define STACK_OPERATIONS_H

# include "stack_core.h"

// Core stack operations
void		push(t_stack *src, t_stack *dest);
void		pa(t_ps *data);
void		pb(t_ps *data);

void		rotate(t_stack *stk);
void		ra(t_ps *data);
void		rb(t_ps *data);
void		rr(t_ps *data);

void		r_rotate(t_stack *stk);
void		rra(t_ps *data);
void		rrb(t_ps *data);
void		rrr(t_ps *data);

void		swap(t_stack *stk);
void		sa(t_ps *data);
void		sb(t_ps *data);
void		ss(t_ps *data);

// Operation tracking
void		save_op(t_ps *data, t_op op);
void		increment_op_count(t_ps *data);
void		print_operations(t_list *head);
void		display_operation_stats(t_ps *data);
const char	*op_to_string(t_op op);
t_op		op_from(t_list *node);

#endif
