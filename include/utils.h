/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:18:55 by codespace         #+#    #+#             */
/*   Updated: 2025/07/17 09:06:06 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include <limits.h>
# include "stack.h"

// Forward declarations
typedef struct s_ps		t_ps;

// Hash table threshold for optimization
# define HASH_TABLE_THRESHOLD 100000
# define INITIAL_OP_CAPACITY 100
# define MAX_OPERATIONS 10000

// Math utilities
int			ft_sqrt(int num);

// Stack utilities
int			get_stack_element_at_position(t_stack *stk, int position);
int			get_current_stack_size(t_stack *stk);
int			calculate_next_up_index(t_stack *stk, int index);
int			calculate_next_down_index(t_stack *stk, int index);
bool		check_if_stack_is_full(t_stack *stk);
bool		check_if_stack_is_empty(t_stack *stk);

//CLEANUP
void		cleanup_and_exit_with_error(t_ps *data);
void		release_allocated_memory(t_ps *data);
void		remove_op_from_list(t_list **list, t_list *to_remove);
// Main utilities
void		print_algorithm_name(int mode);
int			find_min_value_in_stack(t_stack *stack);
bool		is_consecutive(int a, int b, int c, int d);
#endif