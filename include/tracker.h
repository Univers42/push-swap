/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:02:16 by codespace         #+#    #+#             */
/*   Updated: 2025/07/17 01:33:40 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACKER_H
# define TRACKER_H

# include "stack.h"

// Forward declaration only (don't redefine)
typedef struct s_ps	t_ps;

// Basic operations
void		pa(t_ps *data);
void		pb(t_ps *data);
void		sa(t_ps *data);
void		sb(t_ps *data);
void		ss(t_ps *data);
void		ra(t_ps *data);
void		rb(t_ps *data);
void		rr(t_ps *data);
void		rra(t_ps *data);
void		rrb(t_ps *data);
void		rrr(t_ps *data);

// Operation tracking
void		save_op(t_ps *data, t_op op);
void		increment_op_count(t_ps *data);
t_op		op_from(t_list *node);

#endif