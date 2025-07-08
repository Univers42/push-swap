/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:42:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 16:14:14 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
# include "algorithms.h"

int	greedy_find_target_position(t_ps *data, int value)
{
	int	size_a;
	int	target_pos;

	size_a = get_current_stack_size(&data->a);
	target_pos = greedy_find_best_target(data, value, size_a);
	if (target_pos == -1)
		target_pos = greedy_find_min_target(data, size_a);
	return (target_pos);
}

int	greedy_find_best_target(t_ps *data, int value, int size_a)
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

int	greedy_find_min_target(t_ps *data, int size_a)
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

int	greedy_calculate_total_cost(int cost_a, int cost_b, int pos_a, int pos_b)
{
	bool	rotate_a_up;
	bool	rotate_b_up;
	int		size_a;
	int		size_b;

	size_a = 100;
	size_b = 100;
	rotate_a_up = (pos_a <= size_a / 2);
	rotate_b_up = (pos_b <= size_b / 2);
	if (rotate_a_up == rotate_b_up)
	{
		if (cost_a > cost_b)
			return (cost_a);
		else
			return (cost_b);
	}
	return (cost_a + cost_b);
}
