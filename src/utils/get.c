/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:46:15 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 14:48:03 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_stack_element_at_position(t_stack *stk, int position)
{
	int	target_index;

	if (position <= 0 || stk->element_count == 0)
		return (0);
	if (position == 1)
		return (stk->stack[stk->top]);
	target_index = (stk->top + (position - 1)) % stk->capacity;
	return (stk->stack[target_index]);
}

int	get_current_stack_size(t_stack *stk)
{
	if (!stk)
		return (0);
	return (stk->element_count);
}

int	calculate_next_up_index(t_stack *stk, int index)
{
	if (index == 0)
		return (stk->capacity - 1);
	return (index - 1);
}

int	calculate_next_down_index(t_stack *stk, int index)
{
	if (index == stk->capacity - 1)
		return (0);
	return (index + 1);
}
