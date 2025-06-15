/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_core.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:16:11 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:17:05 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_CORE_H
# define STACK_CORE_H

# include "libft.h"
# include <limits.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>

# define HASH_TABLE_THRESHOLD 1000000
# define INITIAL_OP_CAPACITY 1000

typedef struct s_stack
{
	int	*stack;
	int	top;
	int	bottom;
	int	capacity;
	int	element_count;
}	t_stack;

typedef struct s_push_swap
{
	t_stack	a;
	t_stack	b;
	t_list	*op_list;
	int		op_count;
	int		op_capacity;
}			t_ps;

typedef enum e_op
{
	OP_NULL,
	OP_PA,
	OP_PB,
	OP_RA,
	OP_RB,
	OP_RR,
	OP_RRA,
	OP_RRB,
	OP_RRR,
	OP_SA,
	OP_SB,
	OP_SS
}			t_op;

// Core data management
void		initialize_push_swap_data(t_ps *data, int argc, char **argv);
void		allocate_and_init_stack(t_ps *data, t_stack *stk, int capacity);
void		cleanup_and_exit_with_error(t_ps *data);
void		checker_cleanup_and_exit_with_error(t_ps *data);
void		release_allocated_memory(t_ps *data);

#endif
