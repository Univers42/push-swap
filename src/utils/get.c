/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:46:15 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/18 16:23:33 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * The fucntion in this file are utilities for working with circular buffer
 * (circular stack). 
 * All those utilites are performant for the push swap problem to access to
 * the values the more efficient way.
 */

 /**
  * retrieves an element at a given position, wrapping aound using `modulo`
  * (%) for circular access.
  */
int	get_items(t_stack *stk, int position)
{
	int	target_index;

	if (position <= 0 || stk->element_count == 0)
		return (0);
	if (position == 1)
		return (stk->stack[stk->top]);
	target_index = (stk->top + (position - 1)) % stk->capacity;
	return (stk->stack[target_index]);
}

/**
 * we retrive from the member of the struct
 */
int	get_stack_size(t_stack *stk)
{
	if (!stk)
		return (0);
	return (stk->element_count);
}

/**
 * move up in the buffer, wrapping around at the ends
*/
int	move_up(t_stack *stk, int index)
{
	if (index == 0)
		return (stk->capacity - 1);
	return (index - 1);
}

// move down in the buffer, wrapping aroound at the ends
int	move_down(t_stack *stk, int index)
{
	if (index == stk->capacity - 1)
		return (0);
	return (index + 1);
}

//iterates throuh the stack using circular indexing
int	find_min(t_stack *stack)
{
	int	current_index;
	int	min_value;
	int	stack_size;
	int	i;

	if (get_stack_size(stack) == 0)
		return (0);
	current_index = stack->top;
	min_value = stack->stack[current_index];
	stack_size = get_stack_size(stack);
	i = 1;
	while (i < stack_size)
	{
		current_index = move_down(stack, current_index);
		if (stack->stack[current_index] < min_value)
			min_value = stack->stack[current_index];
		i++;
	}
	return (min_value);
}
