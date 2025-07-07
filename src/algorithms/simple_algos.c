/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_algos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 20:11:13 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/06 21:16:54 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

/**
the sort three algorithm is just an algorithm that verifies some conditions
and permutes the values if they are complied 
 */
void sort_three(t_ps *ps)
{
    if (!ps || !ps->stack_a || !ps->stack_a->next || !ps->stack_a->next->next)
        return;

    int a = ps->stack_a->value;
    int b = ps->stack_a->next->value;
    int c = ps->stack_a->next->next->value;

    if (a > b && b < c && a < c)
        sa(ps);                             // case: 2 1 3 → 1 2 3
    else if (a > b && b > c)
    {
        sa(ps); 
        rra(ps);                            // case: 3 2 1 → 1 2 3
    }
    else if (a > b && b < c && a > c)
        ra(ps);                             // case: 3 1 2 → 1 2 3
    else if (a < b && b > c && a < c)
    {
        sa(ps); 
        ra(ps);                             // case: 1 3 2 → 3 1 2 → rotate to 1 2 3
    }
    else if (a < b && b > c && a > c)
        rra(ps);                            // case: 2 3 1 → 1 2 3
}

void sort_two(t_ps *ps)
{
    if (!ps || !ps->stack_a || !ps->stack_a->next)
        return;

    int a = ps->stack_a->value;
    int b = ps->stack_a->next->value;
    
    if (a > b)
        sa(ps);
}