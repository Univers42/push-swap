/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 01:48:06 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/22 02:25:53 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate(t_stack *stk);

/**
 * @brief Rotates stack A upwards (top element becomes bottom).
 * 
 * Example trace:
 *   Before: A = [3, 2, 1] (top = 3)
 *   ra()
 *   After:  A = [2, 1, 3] (top = 2)
 */
void	ra(t_ps *data)
{
	rotate(&data->a);
	save_op(data, OP_RA);
}

/**
 * @brief Rotates stack B upwards (top element becomes bottom).
 * 
 * Example trace:
 *   Before: B = [5, 4, 6] (top = 5)
 *   rb()
 *   After:  B = [4, 6, 5] (top = 4)
 */
void	rb(t_ps *data)
{
	rotate(&data->b);
	save_op(data, OP_RB);
}

/**
 * @brief Rotates both stacks A and B upwards.
 * 
 * Example trace:
 *   Before: A = [3, 2, 1], B = [5, 4, 6]
 *   rr()
 *   After:  A = [2, 1, 3], B = [4, 6, 5]
 */
void	rr(t_ps *data)
{
	rotate(&data->a);
	rotate(&data->b);
	save_op(data, OP_RR);
}

/**
 * @brief Rotates a stack upwards (top element becomes bottom).
 * 
 * Detailed trace:
 *   stk: [T, X, Y, Z] (top = T)
 *   rotate(stk)
 *   Result: [X, Y, Z, T] (top = X)
 * 
 * Handles circular buffer indices and updates top/bottom.
 */
static void	rotate(t_stack *stk)
{
	int	new_top;
	int	new_bottom;

	if (get_stack_size(stk) < 2)
		return ;
	new_top = move_down(stk, stk->top);
	if (get_stack_size(stk) == stk->capacity)
	{
		stk->bottom = stk->top;
		stk->top = new_top;
	}
	else
	{
		new_bottom = move_down(stk, stk->bottom);
		stk->stack[new_bottom] = stk->stack[stk->top];
		stk->stack[stk->top] = 0;
		stk->bottom = new_bottom;
		stk->top = new_top;
	}
}
