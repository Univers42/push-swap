/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:08:57 by ugerkens          #+#    #+#             */
/*   Updated: 2025/06/14 23:55:22 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

void	swap(t_stack *stk)
{
	int	tmp;
	int	second_pos;

	if (get_current_stack_size(stk) < 2)
		return ;
	second_pos = calculate_next_down_index(stk, stk->top);
	tmp = stk->stack[stk->top];
	stk->stack[stk->top] = stk->stack[second_pos];
	stk->stack[second_pos] = tmp;
}

void	sa(t_ps *data)
{
	swap(&data->a);
	save_op(data, OP_SA);
}

void	sb(t_ps *data)
{
	swap(&data->b);
	save_op(data, OP_SB);
}

void	ss(t_ps *data)
{
	swap(&data->a);
	swap(&data->b);
	save_op(data, OP_SS);
}
