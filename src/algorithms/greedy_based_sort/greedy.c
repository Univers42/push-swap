/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:52:32 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 22:56:11 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "debugger.h"

static void	greedy_push_to_b(t_ps *data);
static void	greedy_push_back_to_a(t_ps *data);
static void	greedy_final_rotation(t_ps *data);

void	greedy_sort(t_ps *data)
{
	if (!data || get_current_stack_size(&data->a) <= 3)
	{
		if (get_current_stack_size(&data->a) == 3)
			sort_three_simple(data);
		else if (get_current_stack_size(&data->a) == 2
			&& get_stack_element_at_position(&data->a, 1)
			> get_stack_element_at_position(&data->a, 2))
			sa(data);
		return ;
	}
	if (verify_stack_is_sorted(data))
		return ;
	debug_print_algorithm_start("GREEDY", get_current_stack_size(&data->a));
	debug_print_stack_state(data, "Starting Greedy algorithm");
	greedy_push_to_b(data);
	debug_print_stack_state(data, "After pushing to B");
	greedy_push_back_to_a(data);
	debug_print_stack_state(data, "After pushing back to A");
	greedy_final_rotation(data);
	debug_print_stack_state(data, "After final rotation");
	debug_print_algorithm_end("GREEDY", data);
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
	t_greedy_node	*nodes;
	int				size_b;
	int				cheapest_idx;

	while (get_current_stack_size(&data->b) > 0)
	{
		size_b = get_current_stack_size(&data->b);
		nodes = malloc(sizeof(t_greedy_node) * size_b);
		if (!nodes)
			cleanup_and_exit_with_error(data);
		greedy_calculate_costs(data, nodes, size_b);
		cheapest_idx = greedy_find_cheapest(nodes, size_b);
		greedy_execute_move(data, &nodes[cheapest_idx]);
		free(nodes);
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
