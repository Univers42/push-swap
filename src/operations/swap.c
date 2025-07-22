/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 01:48:15 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/22 01:53:07 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap(t_stack *stk);

/**
 * @brief Swaps the top two elements of stack A.
 * 
 * Example trace:
 *   Before: A = [3, 2, 1] (top = 3)
 *   sa()
 *   After:  A = [2, 3, 1] (top = 2)
 */
void	sa(t_ps *data)
{
	swap(&data->a);
	save_op(data, OP_SA);
}

/**
 * @brief Swaps the top two elements of stack B.
 * 
 * Example trace:
 *   Before: B = [5, 4, 6] (top = 5)
 *   sb()
 *   After:  B = [4, 5, 6] (top = 4)
 */
void	sb(t_ps *data)
{
	swap(&data->b);
	save_op(data, OP_SB);
}

/**
 * @brief Swaps the top two elements of both stacks A and B.
 * 
 * Example trace:
 *   Before: A = [3, 2, 1], B = [5, 4, 6]
 *   ss()
 *   After:  A = [2, 3, 1], B = [4, 5, 6]
 */
void	ss(t_ps *data)
{
	swap(&data->a);
	swap(&data->b);
	save_op(data, OP_SS);
}

/**
 * @brief Swaps the top two elements of a stack.
 * 
 * Detailed trace:
 *   stk: [T, X, Y] (top = T)
 *   swap(stk)
 *   Result: [X, T, Y] (top = X)
 * 
 * Does nothing if stack has fewer than 2 elements.
 */
static void	swap(t_stack *stk)
{
	int	tmp;
	int	second_pos;

	if (get_stack_size(stk) < 2)
		return ;
	second_pos = move_down(stk, stk->top);
	tmp = stk->stack[stk->top];
	stk->stack[stk->top] = stk->stack[second_pos];
	stk->stack[second_pos] = tmp;
}
