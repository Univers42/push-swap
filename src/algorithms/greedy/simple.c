/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:43:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/08 18:49:35 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_three_simple(t_ps *data)
{
	int	first;
	int	second;
	int	third;

	if (get_current_stack_size(&data->a) != 3)
		return ;
	first = get_stack_element_at_position(&data->a, 1);
	second = get_stack_element_at_position(&data->a, 2);
	third = get_stack_element_at_position(&data->a, 3);
	if (first > second && second < third && first < third)
		sa(data);
	else if (first > second && second > third)
	{
		sa(data);
		rra(data);
	}
	else if (first > second && second < third && first > third)
		ra(data);
	else if (first < second && second > third && first < third)
	{
		sa(data);
		ra(data);
	}
	else if (first < second && second > third && first > third)
		rra(data);
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
