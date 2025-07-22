/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 01:48:02 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/22 02:25:40 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "stack.h"

static void	push(t_stack *src, t_stack *dest);

/**
 * @brief Pushes the top element from stack B to stack A.
 * 
 * Example trace:
 *   Before: A = [3, 2], B = [5, 4] (top on the left)
 *   pa()
 *   After:  A = [5, 3, 2], B = [4]
 */
void	pa(t_ps *data)
{
	push(&data->b, &data->a);
	save_op(data, OP_PA);
}

/**
 * @brief Pushes the top element from stack A to stack B.
 * 
 * Example trace:
 *   Before: A = [3, 2], B = [5, 4] (top on the left)
 *   pb()
 *   After:  A = [2], B = [3, 5, 4]
 */
void	pb(t_ps *data)
{
	push(&data->a, &data->b);
	save_op(data, OP_PB);
}

/**
 * @brief Moves the top element from src stack to dest stack.
 * 
 * Detailed trace:
 *   src:  [S1, S2, S3] (top = S1)
 *   dest: [D1, D2]     (top = D1)
 *   push(src, dest)
 *   Result:
 *     src:  [S2, S3]         (top = S2)
 *     dest: [S1, D1, D2]     (top = S1)
 * 
 * Handles circular buffer indices and updates element counts.
 */
static void	push(t_stack *src, t_stack *dest)
{
	int	new_dest_top;
	int	new_src_top;

	if (get_stack_size(dest) == dest->capacity
		|| get_stack_size(src) == 0)
		return ;
	new_dest_top = move_up(dest, dest->top);
	new_src_top = move_down(src, src->top);
	dest->stack[new_dest_top] = src->stack[src->top];
	dest->top = new_dest_top;
	dest->element_count++;
	src->stack[src->top] = 0;
	src->top = new_src_top;
	src->element_count--;
	if (dest->element_count == 1)
		dest->bottom = new_dest_top;
}
