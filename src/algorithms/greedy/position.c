/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:42:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/17 09:24:20 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

int	find_target_position(t_ps *data, int value)
{
	int	size_a;
	int	target_pos;

	size_a = get_current_stack_size(&data->a);
	target_pos = find_best_target(data, value, size_a);
	if (target_pos == -1)
		target_pos = find_min_target(data, size_a);
	return (target_pos);
}

int	find_best_target(t_ps *data, int value, int size_a)
{
	int	current_index;
	int	best_target;
	int	target_pos;
	int	current_value;
	int	i;

	current_index = data->a.top;
	best_target = INT_MAX;
	target_pos = -1;
	i = 0;
	while (i < size_a)
	{
		current_value = data->a.stack[current_index];
		if (current_value > value && current_value < best_target)
		{
			best_target = current_value;
			target_pos = i;
		}
		current_index = calculate_next_down_index(&data->a, current_index);
		i++;
	}
	return (target_pos);
}

int	find_min_target(t_ps *data, int size_a)
{
	int	min_value;
	int	current_index;
	int	target_pos;
	int	i;

	min_value = find_min_value_in_stack(&data->a);
	current_index = data->a.top;
	target_pos = 0;
	i = 0;
	while (i < size_a)
	{
		if (data->a.stack[current_index] == min_value)
		{
			target_pos = i;
			break ;
		}
		current_index = calculate_next_down_index(&data->a, current_index);
		i++;
	}
	return (target_pos);
}

int	find_min_pos(t_ps *data, int size_a, int min_value)
{
	int	current_index;
	int	min_pos;
	int	i;

	current_index = data->a.top;
	min_pos = 0;
	i = 0;
	while (i < size_a)
	{
		if (data->a.stack[current_index] == min_value)
		{
			min_pos = i;
			break ;
		}
		current_index = calculate_next_down_index(&data->a, current_index);
		i++;
	}
	return (min_pos);
}


int	find_cheapest(t_greedy_node *nodes, int size)
{
	int	cheapest_idx;
	int	min_cost;
	int	i;

	cheapest_idx = 0;
	min_cost = nodes[0].total_cost;
	i = 1;
	while (i < size)
	{
		if (nodes[i].total_cost < min_cost)
		{
			min_cost = nodes[i].total_cost;
			cheapest_idx = i;
		}
		i++;
	}
	return (cheapest_idx);
}
