/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:40:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/18 16:13:24 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

/**
 * push_element_strategically - Pushes an element from A to B with strategic rotation.
 * @data: Pointer to the main push_swap data structure.
 * @current: The value of the current element in A.
 * @total_size: The total size of the original stack A.
 *
 * Decides whether to rotate B after pushing based on the value's position.
 * This helps distribute values in B for optimal merging later.
 *
 * Example:
 *   If current is in the first third, pushes and rotates B.
 *   If in the last third, just pushes.
 *   Otherwise, pushes and may rotate B if the top of B is small.
 */
void	push_element_strategically(t_ps *data, int current,
		int total_size)
{
	if (current <= total_size / 3)
	{
		pb(data);
		if (get_stack_size(&data->b) > 1)
			rb(data);
	}
	else if (current >= 2 * total_size / 3)
	{
		pb(data);
	}
	else
	{
		pb(data);
		if (get_stack_size(&data->b) > 1
			&& get_items(&data->b, 1) < total_size / 2)
			rb(data);
	}
}

/**
 * push_to_b - Pushes all but three elements from A to B, using strategic logic.
 * @data: Pointer to the main push_swap data structure.
 *
 * Pushes two elements to B initially, then continues pushing until only three remain in A.
 * Uses push_element_strategically() for each push.
 * Finally, sorts the remaining three in A.
 */
void	push_to_b(t_ps *data)
{
	int	total_size;
	int	current;

	total_size = get_stack_size(&data->a);
	if (total_size > 3)
	{
		pb(data);
		pb(data);
	}
	while (get_stack_size(&data->a) > 3)
	{
		current = get_items(&data->a, 1);
		push_element_strategically(data, current, total_size);
	}
	if (get_stack_size(&data->a) == 3)
		sort_three_simple(data);
}

/**
 * push_back_to_a - Pushes all elements from B back to A in optimal order.
 * @data: Pointer to the main push_swap data structure.
 *
 * For each element in B:
 *   - Calculates move costs for all nodes.
 *   - Finds the cheapest node to move.
 *   - Executes the move.
 *   - Frees the nodes array.
 * Continues until B is empty.
 */
void	push_back_to_a(t_ps *data)
{
	int				size_b;
	int				cheapest_idx;

	while (get_stack_size(&data->b) > 0)
	{
		size_b = get_stack_size(&data->b);
		data->algo_ctx.u_ctx.s_greedy.nodes
			= malloc(sizeof(t_greedy_node) * size_b);
		if (!data->algo_ctx.u_ctx.s_greedy.nodes)
			cleanup_and_exit_with_error(data);
		data->algo_ctx.u_ctx.s_greedy.nodes_count = size_b;
		calculate_costs(data,
			data->algo_ctx.u_ctx.s_greedy.nodes, size_b);
		cheapest_idx
			= find_cheapest(data->algo_ctx.u_ctx.s_greedy.nodes, size_b);
		execute_move(data,
			&data->algo_ctx.u_ctx.s_greedy.nodes[cheapest_idx]);
		free(data->algo_ctx.u_ctx.s_greedy.nodes);
		data->algo_ctx.u_ctx.s_greedy.nodes = NULL;
		data->algo_ctx.u_ctx.s_greedy.nodes_count = 0;
	}
}

