/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/07 16:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

// Initialize a stack with given capacity
void init_stack(t_stack *stack, int capacity)
{
    if (!stack || capacity <= 0)
        return;
    
    stack->stack = malloc(sizeof(int) * capacity);
    if (!stack->stack)
        return;
    
    stack->top = 0;
    stack->capacity = capacity;
    stack->element_count = 0;
    
    // Initialize array to 0
    ft_memset(stack->stack, 0, sizeof(int) * capacity);
}

// Free stack memory
void free_stack(t_stack *stack)
{
    if (!stack)
        return;
    
    if (stack->stack)
    {
        free(stack->stack);
        stack->stack = NULL;
    }
    
    stack->top = 0;
    stack->capacity = 0;
    stack->element_count = 0;
}

// Get current stack size
int get_stack_size(t_stack *stack)
{
    if (!stack)
        return (0);
    return (stack->element_count);
}

// Check if stack is sorted
int is_sorted(t_stack *stack)
{
    int i;
    
    if (!stack || stack->element_count <= 1)
        return (1);
    
    for (i = 0; i < stack->element_count - 1; i++)
    {
        if (stack->stack[i] > stack->stack[i + 1])
        {
            ft_printf("DEBUG: is_sorted - NOT sorted at position %d: %d > %d\n", 
                     i, stack->stack[i], stack->stack[i + 1]);
            return (0);
        }
    }
    ft_printf("DEBUG: is_sorted - Stack IS sorted\n");
    return (1);
}

// Get maximum value in stack
int get_max_value(t_stack *stack)
{
    int i;
    int max;
    
    if (!stack || stack->element_count == 0)
        return (0);
    
    max = stack->stack[0];
    for (i = 1; i < stack->element_count; i++)
    {
        if (stack->stack[i] > max)
            max = stack->stack[i];
    }
    return (max);
}

// Get minimum value in stack
int get_min_value(t_stack *stack)
{
    int i;
    int min;
    
    if (!stack || stack->element_count == 0)
        return (0);
    
    min = stack->stack[0];
    for (i = 1; i < stack->element_count; i++)
    {
        if (stack->stack[i] < min)
            min = stack->stack[i];
    }
    return (min);
}

// Find position of minimum value
int find_min_position(t_stack *stack)
{
    int i;
    int min;
    int min_pos;
    
    if (!stack || stack->element_count == 0)
        return (-1);
    
    min = stack->stack[0];
    min_pos = 0;
    
    for (i = 1; i < stack->element_count; i++)
    {
        if (stack->stack[i] < min)
        {
            min = stack->stack[i];
            min_pos = i;
        }
    }
    return (min_pos);
}

// Get value at specific position (1-based for compatibility)
int get_value_at_position(t_stack *stack, int position)
{
    if (!stack || position <= 0 || position > stack->element_count)
        return (0);
    
    // Convert 1-based position to 0-based index
    return (stack->stack[position - 1]);
}
