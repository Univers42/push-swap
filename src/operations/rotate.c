/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:08:52 by ugerkens          #+#    #+#             */
/*   Updated: 2025/07/18 16:10:20 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate(t_stack *stk);

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
