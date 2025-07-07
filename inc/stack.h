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

#ifndef FT_CHECK_STACK_H
#define FT_CHECK_STACK_H
#include "libft.h"
/**
 * full compatibility approach with the current t_stack structure,
 * all functions that use t_stack still work
 * we can access the underlying `t_stack` directly when needed
 * no breaking chnages to existing code
 * @note strategic use :
 * stck operation(push, pop, rotate)
 * when we need size tracking
 * when we want circular/linear flexibility
 * 
 */
typedef struct s_stack
{
    int value;
    int index;
    int pos;
    int target_pos;
    int cost_a;
    int cost_b;
    int *stack;
    int top;
    int capacity;
    int bottom;
    int element_count;
    struct s_stack *head;
    struct s_stack *tail;
    int size;
    bool is_circular;
    struct s_stack *next;
}               t_stack;


int get_stack_size(t_stack*stack);
int is_sorted(t_stack *stack);
int get_max_value(t_stack *stack);
int get_min_value(t_stack *stack);
int find_min_position(t_stack *stack);
t_stack *create_int_node(int value);
#endif