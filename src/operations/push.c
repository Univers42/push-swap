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
// External recorder functions (declare these in ps.h)
extern void record_operation(const char *operation);
extern int is_recording(void);

/**
 * Generic push function that moves the top element from source to destination
 * @param source Pointer to the source stack head
 * @param dest Pointer to the destination stack head  
 * @param size_src Pointer to source stack size
 * @param size_dest Pointer to destination stack size
 */
static void push(t_list **source, t_list **dest, int *size_src, int *size_dest)
{
    t_list *temp;
    
    if (!*source || *size_src == 0)
        return;
    
    // Remove from source
    temp = *source;
    *source = (*source)->next;
    if (*source)
        (*source)->prev = NULL;
    
    // Add to destination
    temp->next = *dest;
    temp->prev = NULL;
    if (*dest)
        (*dest)->prev = temp;
    *dest = temp;
    
    // Update sizes
    (*size_src)--;
    (*size_dest)++;
}

/**
 * Push from stack A to stack B
 */
void pb(t_ps *ps)
{
    push(&ps->stack_a, &ps->stack_b, &ps->size_a, &ps->size_b);
    
    if (is_recording())
        record_operation("pb");
    else
        ft_printf("pb\n");
}

/**
 * Push from stack B to stack A
 */
void pa(t_ps *ps)
{
    push(&ps->stack_b, &ps->stack_a, &ps->size_b, &ps->size_a);
    
    if (is_recording())
        record_operation("pa");
    else
        ft_printf("pa\n");
}
