/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_buffer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/07 17:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

void init_op_buffer(t_op_buffer *buffer, int capacity)
{
    if (!buffer || capacity <= 0)
        return;
    
    buffer->operations = malloc(sizeof(char *) * capacity);
    if (!buffer->operations)
        return;
    
    buffer->count = 0;
    buffer->capacity = capacity;
    
    // Initialize all pointers to NULL
    for (int i = 0; i < capacity; i++)
        buffer->operations[i] = NULL;
}

void free_op_buffer(t_op_buffer *buffer)
{
    if (!buffer || !buffer->operations)
        return;
    
    // Free each operation string
    for (int i = 0; i < buffer->count; i++)
    {
        if (buffer->operations[i])
        {
            free(buffer->operations[i]);
            buffer->operations[i] = NULL;
        }
    }
    
    // Free the operations array
    free(buffer->operations);
    buffer->operations = NULL;
    buffer->count = 0;
    buffer->capacity = 0;
}

void append_operation(t_ps *ps, const char *op)
{
    if (!ps || !op || !ps->op_buffer.operations)
        return;
    
    // Check if buffer is full
    if (ps->op_buffer.count >= ps->op_buffer.capacity)
        return;
    
    // Duplicate the operation string
    ps->op_buffer.operations[ps->op_buffer.count] = ft_strdup(op);
    if (ps->op_buffer.operations[ps->op_buffer.count])
        ps->op_buffer.count++;
}

void print_operations(t_ps *ps)
{
    if (!ps || !ps->op_buffer.operations)
        return;
    
    ft_printf("=== Operations Buffer (%d operations) ===\n", ps->op_buffer.count);
    for (int i = 0; i < ps->op_buffer.count; i++)
    {
        if (ps->op_buffer.operations[i])
            ft_printf("%s\n", ps->op_buffer.operations[i]);
    }
    ft_printf("=====================================\n");
}

void clear_operations(t_ps *ps)
{
    if (!ps || !ps->op_buffer.operations)
        return;
    
    // Free each operation string
    for (int i = 0; i < ps->op_buffer.count; i++)
    {
        if (ps->op_buffer.operations[i])
        {
            free(ps->op_buffer.operations[i]);
            ps->op_buffer.operations[i] = NULL;
        }
    }
    
    ps->op_buffer.count = 0;
}
