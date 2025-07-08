/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:38:14 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/06 23:04:40 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

/**
 * Generic push function that moves the top element from source to destination
 * @param source Source stack (array-based)
 * @param dest Destination stack (array-based)
 */
static void push(t_stack *source, t_stack *dest)
{
    if (!source || !dest || source->element_count == 0)
        return;
    
    // Check if destination has space
    if (dest->element_count >= dest->capacity)
        return;
    
    // Get top element from source (index 0)
    int value = source->stack[0];
    
    // Shift all elements in source down by 1
    for (int i = 0; i < source->element_count - 1; i++)
        source->stack[i] = source->stack[i + 1];
    
    // Decrease source count
    source->element_count--;
    
    // Shift all elements in destination up by 1
    for (int i = dest->element_count; i > 0; i--)
        dest->stack[i] = dest->stack[i - 1];
    
    // Add value to top of destination (index 0)
    dest->stack[0] = value;
    dest->element_count++;
}

/**
 * Push from stack A to stack B
 */
void pb(t_ps *ps)
{
    push(&ps->stack_a, &ps->stack_b);
    
    if (ps->recording)
        append_operation(ps, "pb");
    
    if (is_recording())
        record_operation("pb");
    else if (!ps->recording)
        ft_printf("pb\n");
}

/**
 * Push from stack B to stack A
 */
void pa(t_ps *ps)
{
    push(&ps->stack_b, &ps->stack_a);
    
    if (ps->recording)
        append_operation(ps, "pa");
    
    if (is_recording())
        record_operation("pa");
    else if (!ps->recording)
        ft_printf("pa\n");
}
