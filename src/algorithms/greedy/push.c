/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:40:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/17 09:24:03 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

void	push_element_strategically(t_ps *data, int current,
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

void	push_to_b(t_ps *data)
{
	int	total_size;
	int	current;

	total_size = get_current_stack_size(&data->a);
	if (total_size > 3)
	{
		pb(data);
		pb(data);
	}
	while (get_current_stack_size(&data->a) > 3)
	{
		current = get_stack_element_at_position(&data->a, 1);
		push_element_strategically(data, current, total_size);
	}
	if (get_current_stack_size(&data->a) == 3)
		sort_three_simple(data);
}

void	push_back_to_a(t_ps *data)
{
	int				size_b;
	int				cheapest_idx;

	while (get_current_stack_size(&data->b) > 0)
	{
		size_b = get_current_stack_size(&data->b);
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

