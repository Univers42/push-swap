/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:40:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 16:16:51 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
# include "algorithms.h"

void	greedy_push_element_strategically(t_ps *data, int current,
		int total_size)
{
	if (current <= total_size / 3)
	{
		pb(data);
		if (get_current_stack_size(&data->b) > 1)
			rb(data);
	}
	else if (current >= 2 * total_size / 3)
	{
		pb(data);
	}
	else
	{
		pb(data);
		if (get_current_stack_size(&data->b) > 1
			&& get_stack_element_at_position(&data->b, 1) < total_size / 2)
			rb(data);
	}
}

void	greedy_calculate_costs(t_ps *data, t_greedy_node *nodes, int size_b)
{
	int	size_a;
	int	current_index;
	int	i;

	size_a = get_current_stack_size(&data->a);
	current_index = data->b.top;
	i = 0;
	while (i < size_b)
	{
		nodes[i].value = data->b.stack[current_index];
		nodes[i].index = i;
		nodes[i].target_pos = greedy_find_target_position(data, nodes[i].value);
		greedy_calculate_move_costs(&nodes[i], size_a, size_b);
		current_index = calculate_next_down_index(&data->b, current_index);
		i++;
	}
}

void	greedy_calculate_move_costs(t_greedy_node *node, int size_a, int size_b)
{
	if (node->index <= size_b / 2)
		node->cost_b = node->index;
	else
		node->cost_b = size_b - node->index;
	if (node->target_pos <= size_a / 2)
		node->cost_a = node->target_pos;
	else
		node->cost_a = size_a - node->target_pos;
	node->total_cost = greedy_calculate_total_cost(node->cost_a, node->cost_b,
			node->target_pos, node->index);
}

int	greedy_find_cheapest(t_greedy_node *nodes, int size)
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

int	greedy_find_min_pos(t_ps *data, int size_a, int min_value)
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
