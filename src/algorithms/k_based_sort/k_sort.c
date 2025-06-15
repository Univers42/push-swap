/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_sort.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 23:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 23:16:04 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "debugger.h"

static void	k_sort_main_process(t_ps *data, int total_size);

void	k_sort(t_ps *data)
{
	int	total_size;

	if (!data || get_current_stack_size(&data->a) <= 3)
	{
		k_sort_handle_small_arrays(data);
		return ;
	}
	if (verify_stack_is_sorted(data))
		return ;
	total_size = get_current_stack_size(&data->a);
	debug_print_algorithm_start("K-SORT", total_size);
	debug_print_stack_state(data, "Starting K-Sort algorithm");
	k_sort_main_process(data, total_size);
	debug_print_algorithm_end("K-SORT", data);
}

static void	k_sort_main_process(t_ps *data, int total_size)
{
	int	range;
	int	i;
	int	target_remaining;

	range = ft_sqrt(total_size) * 14 / 10;
	i = 1;
	target_remaining = 3;
	k_sort_push_loop(data, &range, &i, target_remaining);
	k_sort_handle_remaining_in_a(data);
	debug_print_stack_state(data, "After K-Sort pushing to B");
	while (get_current_stack_size(&data->b) > 0)
	{
		k_find_and_move_max_to_top(data);
		pa(data);
	}
	debug_print_stack_state(data, "After K-Sort pushing back to A");
	k_sort_apply_final_rotation(data);
	debug_print_stack_state(data, "K-Sort algorithm completed");
}
