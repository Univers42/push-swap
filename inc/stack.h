/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/07 18:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include <stdlib.h>

// Array-based stack structure
typedef struct s_stack
{
    int     *stack;         // Array of integers
    int     element_count;  // Current number of elements
    int     capacity;       // Maximum capacity
    int     top;            // For circular buffer compatibility (always 0 for array)
    int     bottom;         // For circular buffer compatibility (always element_count-1)
}               t_stack;

// Stack initialization and cleanup
void    init_stack(t_stack *stack, int capacity);
void    free_stack(t_stack *stack);

// Stack operations
int     get_stack_size(t_stack *stack);
int     is_sorted(t_stack *stack);
int     get_max_value(t_stack *stack);
int     get_min_value(t_stack *stack);
int     find_min_position(t_stack *stack);
int     get_value_at_position(t_stack *stack, int position);

// For chunk compatibility
int     get_stack_element_at_position(t_stack *stk, int position);
int     get_current_stack_size(t_stack *stk);
int     calculate_next_up_index(t_stack *stk, int index);
int     calculate_next_down_index(t_stack *stk, int index);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/07 18:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include <stdlib.h>

// Array-based stack structure
typedef struct s_stack
{
    int     *stack;         // Array of integers
    int     element_count;  // Current number of elements
    int     capacity;       // Maximum capacity
    int     top;            // For circular buffer compatibility (always 0 for array)
    int     bottom;         // For circular buffer compatibility (always element_count-1)
}               t_stack;

// Stack initialization and cleanup
void    init_stack(t_stack *stack, int capacity);
void    free_stack(t_stack *stack);

// Stack operations
int     get_stack_size(t_stack *stack);
int     is_sorted(t_stack *stack);
int     get_max_value(t_stack *stack);
int     get_min_value(t_stack *stack);
int     find_min_position(t_stack *stack);
int     get_value_at_position(t_stack *stack, int position);

// For chunk compatibility
int     get_stack_element_at_position(t_stack *stk, int position);
int     get_current_stack_size(t_stack *stk);
int     calculate_next_up_index(t_stack *stk, int index);
int     calculate_next_down_index(t_stack *stk, int index);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/07 18:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include <stdlib.h>

// Array-based stack structure
typedef struct s_stack
{
    int     *stack;         // Array of integers
    int     element_count;  // Current number of elements
    int     capacity;       // Maximum capacity
    int     top;            // For circular buffer compatibility (always 0 for array)
    int     bottom;         // For circular buffer compatibility (always element_count-1)
}               t_stack;

// Stack initialization and cleanup
void    init_stack(t_stack *stack, int capacity);
void    free_stack(t_stack *stack);

// Stack operations
int     get_stack_size(t_stack *stack);
int     is_sorted(t_stack *stack);
int     get_max_value(t_stack *stack);
int     get_min_value(t_stack *stack);
int     find_min_position(t_stack *stack);
int     get_value_at_position(t_stack *stack, int position);

// For chunk compatibility
int     get_stack_element_at_position(t_stack *stk, int position);
int     get_current_stack_size(t_stack *stk);
int     calculate_next_up_index(t_stack *stk, int index);
int     calculate_next_down_index(t_stack *stk, int index);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/07 16:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include <stdlib.h>

// Array-based stack structure
typedef struct s_stack
{
    int     *stack;         // Array of integers
    int     element_count;  // Current number of elements
    int     capacity;       // Maximum capacity
    int     top;            // For circular buffer compatibility (always 0 for array)
    int     bottom;         // For circular buffer compatibility (always element_count-1)
}               t_stack;

// Stack initialization and cleanup
void    init_stack(t_stack *stack, int capacity);
void    free_stack(t_stack *stack);

// Stack operations
int     get_stack_size(t_stack *stack);
int     is_sorted(t_stack *stack);
int     get_max_value(t_stack *stack);
int     get_min_value(t_stack *stack);
int     find_min_position(t_stack *stack);
int     get_value_at_position(t_stack *stack, int position);

// For chunk compatibility
int     get_stack_element_at_position(t_stack *stk, int position);
int     get_current_stack_size(t_stack *stk);
int     calculate_next_up_index(t_stack *stk, int index);
int     calculate_next_down_index(t_stack *stk, int index);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 16:30:17 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/07 13:27:17 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
#define STACK_H
#include "libft.h"

#define MAX_STACK_SIZE 10000

/**
 * Pure array-based stack implementation
 * - stack: array of integers
 * - top: index of the top element (0-based)
 * - capacity: maximum capacity of the stack
 * - element_count: current number of elements
 * 
 * @note Stack grows from index 0 upwards
 * Empty stack: element_count = 0
 * Full stack: element_count = capacity
 */
typedef struct s_stack
{
    int *stack;           // Dynamic array of integers
    int top;              // Index of top element
    int capacity;         // Maximum capacity
    int element_count;    // Current number of elements
}               t_stack;

// Stack operations
int     get_stack_size(t_stack *stack);
int     is_sorted(t_stack *stack);
int     get_max_value(t_stack *stack);
int     get_min_value(t_stack *stack);
int     find_min_position(t_stack *stack);
int     get_value_at_position(t_stack *stack, int position);
void    init_stack(t_stack *stack, int capacity);
void    free_stack(t_stack *stack);

#endif