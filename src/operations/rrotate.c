/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rrotate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 01:48:11 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/22 02:26:05 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	r_rotate(t_stack *stk);

/**
 * @brief Reverse rotates stack A (bottom element becomes top).
 * 
 * Example trace:
 *   Before: A = [3, 2, 1] (top = 3)
 *   rra()
 *   After:  A = [1, 3, 2] (top = 1)
 */
void	rra(t_ps *data)
{
	r_rotate(&data->a);
	save_op(data, OP_RRA);
}

/**
 * @brief Reverse rotates stack B (bottom element becomes top).
 * 
 * Example trace:
 *   Before: B = [5, 4, 6] (top = 5)
 *   rrb()
 *   After:  B = [6, 5, 4] (top = 6)
 */
void	rrb(t_ps *data)
{
	r_rotate(&data->b);
	save_op(data, OP_RRB);
}

/**
 * @brief Reverse rotates both stacks A and B.
 * 
 * Example trace:
 *   Before: A = [3, 2, 1], B = [5, 4, 6]
 *   rrr()
 *   After:  A = [1, 3, 2], B = [6, 5, 4]
 */
void	rrr(t_ps *data)
{
	r_rotate(&data->a);
	r_rotate(&data->b);
	save_op(data, OP_RRR);
}

/**
 * @brief Reverse rotates a stack (bottom element becomes top).
 * 
 * Detailed trace:
 *   stk: [T, X, Y, Z] (top = T, bottom = Z)
 *   r_rotate(stk)
 *   Result: [Z, T, X, Y] (top = Z, bottom = Y)
 * 
 * Handles circular buffer indices and updates top/bottom.
 */
static void	r_rotate(t_stack *stk)
{
	int	new_top;
	int	new_bottom;

	if (get_stack_size(stk) < 2)
		return ;
	new_bottom = move_up(stk, stk->bottom);
	if (get_stack_size(stk) == stk->capacity)
	{
		stk->top = stk->bottom;
		stk->bottom = new_bottom;
	}
	else
	{
		new_top = move_up(stk, stk->top);
		stk->stack[new_top] = stk->stack[stk->bottom];
		stk->stack[stk->bottom] = 0;
		stk->top = new_top;
		stk->bottom = new_bottom;
	}
}
