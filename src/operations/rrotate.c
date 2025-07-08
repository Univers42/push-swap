/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rrotate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:08:47 by ugerkens          #+#    #+#             */
/*   Updated: 2025/07/08 14:53:03 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

static void	r_rotate(t_stack *stk);

void	rra(t_ps *data)
{
	r_rotate(&data->a);
	save_op(data, OP_RRA);
}

void	rrb(t_ps *data)
{
	r_rotate(&data->b);
	save_op(data, OP_RRB);
}

void	rrr(t_ps *data)
{
	r_rotate(&data->a);
	r_rotate(&data->b);
	save_op(data, OP_RRR);
}

static void	r_rotate(t_stack *stk)
{
	int	new_top;
	int	new_bottom;

	if (get_current_stack_size(stk) < 2)
		return ;
	new_bottom = calculate_next_up_index(stk, stk->bottom);
	if (get_current_stack_size(stk) == stk->capacity)
	{
		stk->top = stk->bottom;
		stk->bottom = new_bottom;
	}
	else
	{
		new_top = calculate_next_up_index(stk, stk->top);
		stk->stack[new_top] = stk->stack[stk->bottom];
		stk->stack[stk->bottom] = 0;
		stk->top = new_top;
		stk->bottom = new_bottom;
	}
}
