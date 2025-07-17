/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 09:13:42 by codespace         #+#    #+#             */
/*   Updated: 2025/07/17 09:25:25 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

void	calculate_move_costs(t_greedy_node *node, int size_a, int size_b)
{
	if (node->index <= size_b / 2)
		node->cost_b = node->index;
	else
		node->cost_b = size_b - node->index;
	if (node->target_pos <= size_a / 2)
		node->cost_a = node->target_pos;
	else
		node->cost_a = size_a - node->target_pos;
	node->total_cost =  calculate_total_cost(node->cost_a, node->cost_b,
			node->target_pos, node->index);
}

void	calculate_costs(t_ps *data, t_greedy_node *nodes, int size_b)
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
		nodes[i].target_pos =  find_target_position(data, nodes[i].value);
		calculate_move_costs(&nodes[i], size_a, size_b);
		current_index = calculate_next_down_index(&data->b, current_index);
		i++;
	}
}

int	calculate_total_cost(int cost_a, int cost_b, int pos_a, int pos_b)
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
