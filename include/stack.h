/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:56:27 by ugerkens          #+#    #+#             */
/*   Updated: 2025/06/15 17:19:10 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include "../libft/libft.h"
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

// CORE INITIALIZATION
void		initialize_push_swap_data(t_ps *data, int argc, char **argv);
void		allocate_and_init_stack(t_ps *data, t_stack *stk, int capacity);

// STACK CONVERSION AND VALIDATION
void		populate_stack_with_ranks(t_ps *data, t_stack *stk, int size,
				char **arg);
bool		validate_numeric_argument(char *arg);
bool		detect_duplicates_optimized(t_ps *data, int *numbers, int size);
bool		detect_duplicates_with_sorting(int *numbers, int size);
void		convert_numbers_to_ranks(int *numbers, int *rank, int size);
void		efficient_sort(int *arr, int size);

// STACK VERIFICATION AND CLEANUP
bool		verify_stack_is_sorted(t_ps *data);
void		release_allocated_memory(t_ps *data);
void		cleanup_and_exit_with_error(t_ps *data);

// UTILITY FUNCTIONS
int			calculate_next_up_index(t_stack *stk, int index);
int			calculate_next_down_index(t_stack *stk, int index);
int			get_stack_element_at_position(t_stack *stk, int position);
int			get_current_stack_size(t_stack *stk);
bool		check_if_stack_is_full(t_stack *stk);
bool		check_if_stack_is_empty(t_stack *stk);

// OPERATION TRACKING
void		save_op(t_ps *data, t_op op);
void		increment_op_count(t_ps *data);
void		display_operation_stats(t_ps *data);
void		print_operations(t_list *head);
const char	*op_to_string(t_op op);
t_op		op_from(t_list *node);

// CORE STACK OPERATIONS
void		push(t_stack *src, t_stack *dest);
void		pa(t_ps *data);
void		pb(t_ps *data);
void		r_rotate(t_stack *stk);
void		rra(t_ps *data);
void		rrb(t_ps *data);
void		rrr(t_ps *data);
void		rotate(t_stack *stk);
void		ra(t_ps *data);
void		rb(t_ps *data);
void		rr(t_ps *data);
void		swap(t_stack *stk);
void		sa(t_ps *data);
void		sb(t_ps *data);
void		ss(t_ps *data);

void		remove_op(t_list *to_delete);

#endif
