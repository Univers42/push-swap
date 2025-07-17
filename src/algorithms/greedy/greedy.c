/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:52:32 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/17 01:40:06 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

static void	greedy_push_to_b(t_ps *data);
static void	greedy_push_back_to_a(t_ps *data);
static void	greedy_final_rotation(t_ps *data);

void	greedy_sort(t_ps *data)
{
	if (!data || data->total_size <= 3)
	{
		if (data->total_size == 3)
			sort_three_simple(data);
		else if (data->total_size == 2
			&& get_stack_element_at_position(&data->a, 1)
			> get_stack_element_at_position(&data->a, 2))
			sa(data);
		return ;
	}
	if (verify_stack_is_sorted(data))
		return ;
	data->algo_ctx.u_ctx.s_greedy.phase = 0;
	greedy_push_to_b(data);
	data->algo_ctx.u_ctx.s_greedy.phase = 1;
	greedy_push_back_to_a(data);
	greedy_final_rotation(data);
}

static void	greedy_push_to_b(t_ps *data)
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
		greedy_push_element_strategically(data, current, total_size);
	}
	if (get_current_stack_size(&data->a) == 3)
		sort_three_simple(data);
}

static void	greedy_push_back_to_a(t_ps *data)
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
		greedy_calculate_costs(data,
			data->algo_ctx.u_ctx.s_greedy.nodes, size_b);
		cheapest_idx
			= greedy_find_cheapest(data->algo_ctx.u_ctx.s_greedy.nodes, size_b);
		greedy_execute_move(data,
			&data->algo_ctx.u_ctx.s_greedy.nodes[cheapest_idx]);
		free(data->algo_ctx.u_ctx.s_greedy.nodes);
		data->algo_ctx.u_ctx.s_greedy.nodes = NULL;
		data->algo_ctx.u_ctx.s_greedy.nodes_count = 0;
	}
}

static void	greedy_final_rotation(t_ps *data)
{
	int	min_value;
	int	min_pos;
	int	size_a;

	min_value = find_min_value_in_stack(&data->a);
	min_pos = 0;
	size_a = get_current_stack_size(&data->a);
	min_pos = greedy_find_min_pos(data, size_a, min_value);
	greedy_rotate_to_top(data, min_pos, size_a);
}
