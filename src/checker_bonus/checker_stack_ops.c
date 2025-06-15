/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_stack_ops.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 23:15:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 23:13:29 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

void	checker_push(t_stack *src, t_stack *dest)
{
	int	new_dest_top;
	int	new_src_top;

	if (get_current_stack_size(dest) == dest->capacity
		|| get_current_stack_size(src) == 0)
		return ;
	new_dest_top = calculate_next_up_index(dest, dest->top);
	new_src_top = calculate_next_down_index(src, src->top);
	dest->stack[new_dest_top] = src->stack[src->top];
	dest->top = new_dest_top;
	dest->element_count++;
	src->stack[src->top] = 0;
	src->top = new_src_top;
	src->element_count--;
	if (dest->element_count == 1)
		dest->bottom = new_dest_top;
}

void	checker_swap(t_stack *stk)
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

void	checker_rotate(t_stack *stk)
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

void	checker_r_rotate(t_stack *stk)
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
