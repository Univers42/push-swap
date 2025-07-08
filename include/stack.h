/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:56:27 by ugerkens          #+#    #+#             */
/*   Updated: 2025/06/16 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include "push_swap.h"

// Forward compatibility layer for stack operations
void		push(t_stack *src, t_stack *dest);
void		r_rotate(t_stack *stk);
void		rotate(t_stack *stk);
void		swap(t_stack *stk);

// Remove op from list
void		remove_op(t_list *to_delete);

// Math utilities (avoid circular dependency)
void		quick_sort_int(int *arr, int low, int high);
int			ft_sqrt(int nb);

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
void		display_operation_stats(t_ps *data);
void		print_operations(t_list *head);
const char	*op_to_string(t_op op);
t_op		op_from(t_list *node);


void		remove_op(t_list *to_delete);

#endif
