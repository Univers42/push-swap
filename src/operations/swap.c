/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:08:57 by ugerkens          #+#    #+#             */
/*   Updated: 2025/07/08 14:53:41 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

static void	swap(t_stack *stk);

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

static void	swap(t_stack *stk)
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