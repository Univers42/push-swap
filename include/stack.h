/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:56:27 by ugerkens          #+#    #+#             */
/*   Updated: 2025/07/17 09:06:46 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include <stdlib.h>
# include <stdbool.h>
# include "libft.h"

// Forward declarations
typedef struct s_ps		t_ps;

// Stack structure
typedef struct s_stack
{
	int		*stack;
	int		top;
	int		bottom;
	int		capacity;
	int		element_count;
}	t_stack;

// Operation enum
typedef enum e_op
{
	OP_NULL = 0,
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
}	t_op;

// Location enum for chunk sorting
typedef enum e_loc
{
	TOP_A,
	TOP_B,
	BOTTOM_A,
	BOTTOM_B
}	t_loc;

// STACK CONVERSION AND VALIDATION
void		populate_stack_with_ranks(t_ps *data, t_stack *stk, int size,
				char **arg);
bool		validate_numeric_argument(char *arg);
bool		detect_duplicates_optimized(t_ps *data, int *numbers, int size);
bool		detect_duplicates_with_sorting(int *numbers, int size);
void		efficient_sort(int *arr, int size);

// STACK VERIFICATION AND CLEANUP
bool		verify_stack_is_sorted(t_ps *data);
void		release_allocated_memory(t_ps *data);
void		cleanup_and_exit_with_error(t_ps *data);

// OPERATION TRACKING
void		save_op(t_ps *data, t_op op);
void		increment_op_count(t_ps *data);
void		display_operation_stats(t_ps *data);
void		print_operations(t_list *head);
const char	*op_to_string(t_op op);
t_op		op_from(t_list *node);

// Stack operations
void		allocate_and_init_stack(t_ps *data, t_stack *stk, int capacity);
void		convert_numbers_to_ranks(int *numbers, int *rank, int size);

// Stack utility functions
int			get_stack_element_at_position(t_stack *stk, int position);
int			get_current_stack_size(t_stack *stk);
int			calculate_next_up_index(t_stack *stk, int index);
int			calculate_next_down_index(t_stack *stk, int index);
bool		check_if_stack_is_full(t_stack *stk);
bool		check_if_stack_is_empty(t_stack *stk);

#endif
