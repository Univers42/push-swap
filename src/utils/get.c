/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:46:15 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/17 09:07:57 by codespace        ###   ########.fr       */
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

int	find_min_value_in_stack(t_stack *stack)
{
	int	current_index;
	int	min_value;
	int	stack_size;
	int	i;

	if (get_current_stack_size(stack) == 0)
		return (0);
	current_index = stack->top;
	min_value = stack->stack[current_index];
	stack_size = get_current_stack_size(stack);
	i = 1;
	while (i < stack_size)
	{
		current_index = calculate_next_down_index(stack, current_index);
		if (stack->stack[current_index] < min_value)
			min_value = stack->stack[current_index];
		i++;
	}
	return (min_value);
}
