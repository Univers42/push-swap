/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:17:52 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:18:17 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_UTILS_H
# define STACK_UTILS_H

# include "stack_core.h"

// Stack utility functions
int			calculate_next_up_index(t_stack *stk, int index);
int			calculate_next_down_index(t_stack *stk, int index);
int			get_stack_element_at_position(t_stack *stk, int position);
int			get_current_stack_size(t_stack *stk);
bool		check_if_stack_is_full(t_stack *stk);
bool		check_if_stack_is_empty(t_stack *stk);

// Stack verification
bool		verify_stack_is_sorted(t_ps *data);

// Input validation and conversion
bool		validate_numeric_argument(char *arg);
void		populate_stack_with_ranks(t_ps *data, t_stack *stk, int size,
				char **arg);
bool		detect_duplicates_optimized(t_ps *data, int *numbers, int size);
bool		detect_duplicates_with_sorting(int *numbers, int size);
void		convert_numbers_to_ranks(int *numbers, int *rank, int size);
void		efficient_sort(int *arr, int size);
#endif
