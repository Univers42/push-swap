/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:02:42 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/06 23:01:20 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

/**
 * Move all elements up by one position
 * First element becomes last element
 * @param stack Array-based stack
 */
static void rotate_stack(t_stack *stack)
{
    int first;
    int i;
    
    if (!stack || stack->element_count < 2)
        return;
    
    // Save first element
    first = stack->stack[0];
    
    // Shift all elements down by 1
    for (i = 0; i < stack->element_count - 1; i++)
        stack->stack[i] = stack->stack[i + 1];
    
    // Put first element at the end
    stack->stack[stack->element_count - 1] = first;
}

void ra(t_ps *ps)
{
    rotate_stack(&ps->stack_a);
    
    if (ps->recording)
        append_operation(ps, "ra");
    
    if (is_recording())
        record_operation("ra");
    else if (!ps->recording)
        ft_printf("ra\n");
}

void rb(t_ps *ps)
{
    rotate_stack(&ps->stack_b);
    
    if (ps->recording)
        append_operation(ps, "rb");
    
    if (is_recording())
        record_operation("rb");
    else if (!ps->recording)
        ft_printf("rb\n");
}

void rr(t_ps *ps)
{
    rotate_stack(&ps->stack_a);
    rotate_stack(&ps->stack_b);
    
    if (ps->recording)
        append_operation(ps, "rr");
    
    if (is_recording())
        record_operation("rr");
    else if (!ps->recording)
        ft_printf("rr\n");
}
