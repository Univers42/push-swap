/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:08:52 by ugerkens          #+#    #+#             */
/*   Updated: 2025/06/14 23:55:21 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

void	rotate(t_stack *stk)
{
	int	new_top;
	int	new_bottom;

	if (get_current_stack_size(stk) < 2)
		return ;
	new_top = calculate_next_down_index(stk, stk->top);
	if (get_current_stack_size(stk) == stk->capacity)
	{
		stk->bottom = stk->top;
		stk->top = new_top;
	}
	else
	{
		new_bottom = calculate_next_down_index(stk, stk->bottom);
		stk->stack[new_bottom] = stk->stack[stk->top];
		stk->stack[stk->top] = 0;
		stk->bottom = new_bottom;
		stk->top = new_top;
	}
}

void	ra(t_ps *data)
{
	rotate(&data->a);
	save_op(data, OP_RA);
}

void	rb(t_ps *data)
{
	rotate(&data->b);
	save_op(data, OP_RB);
}

void	rr(t_ps *data)
{
	rotate(&data->a);
	rotate(&data->b);
	save_op(data, OP_RR);
}
