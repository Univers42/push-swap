/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rrotate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:19:42 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/06 23:01:40 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

/**
 * Move the last element to the front (reverse rotate)
 * Last element becomes first element
 * @param stack Array-based stack
 */
static void reverse_rotate_stack(t_stack *stack)
{
    int last;
    int i;
    
    if (!stack || stack->element_count < 2)
        return;
    
    // Save last element
    last = stack->stack[stack->element_count - 1];
    
    // Shift all elements up by 1
    for (i = stack->element_count - 1; i > 0; i--)
        stack->stack[i] = stack->stack[i - 1];
    
    // Put last element at the beginning
    stack->stack[0] = last;
}

void rra(t_ps *ps)
{
    reverse_rotate_stack(&ps->stack_a);
    
    if (ps->recording)
        append_operation(ps, "rra");
    
    if (is_recording())
        record_operation("rra");
    else if (!ps->recording)
        ft_printf("rra\n");
}

void rrb(t_ps *ps)
{
    reverse_rotate_stack(&ps->stack_b);
    
    if (ps->recording)
        append_operation(ps, "rrb");
    
    if (is_recording())
        record_operation("rrb");
    else if (!ps->recording)
        ft_printf("rrb\n");
}

void rrr(t_ps *ps)
{
    reverse_rotate_stack(&ps->stack_a);
    reverse_rotate_stack(&ps->stack_b);
    
    if (ps->recording)
        append_operation(ps, "rrr");
    
    if (is_recording())
        record_operation("rrr");
    else if (!ps->recording)
        ft_printf("rrr\n");
}