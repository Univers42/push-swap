/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 23:16:45 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "debugger.h"

void	print_algorithm_name(int mode)
{
	if (is_algorithm_mode(mode, MODE_GREEDY_ALGO))
		debug_set_algorithm("GREEDY");
	else if (is_algorithm_mode(mode, MODE_ALTERNATIVE_ALGO))
		debug_set_algorithm("K-SORT");
	else if (is_algorithm_mode(mode, MODE_HYBRID_ALGO))
		debug_set_algorithm("HYBRID");
	else if (is_algorithm_mode(mode, MODE_K_SORT_ALGO))
		debug_set_algorithm("K-SORT");
	else if (is_algorithm_mode(mode, MODE_RADIX_ALGO))
		debug_set_algorithm("RADIX");
	else if (is_algorithm_mode(mode, MODE_LIS_ALGO))
		debug_set_algorithm("LIS");
	else if (is_algorithm_mode(mode, MODE_QUEUE_ALGO))
		debug_set_algorithm("QUEUE");
	else
		debug_set_algorithm("CHUNK");
}

void	execute_selected_algorithm(t_ps *data, int mode)
{
	if (is_algorithm_mode(mode, MODE_GREEDY_ALGO))
		greedy_sort(data);
	else if (is_algorithm_mode(mode, MODE_ALTERNATIVE_ALGO))
		k_sort(data);
	else if (is_algorithm_mode(mode, MODE_HYBRID_ALGO))
		sort(data);
	else if (is_algorithm_mode(mode, MODE_K_SORT_ALGO))
		k_sort(data);
	else if (is_algorithm_mode(mode, MODE_RADIX_ALGO))
		radix_sort(data);
	else if (is_algorithm_mode(mode, MODE_LIS_ALGO))
		lis_sort(data);
	else
		sort(data);
}

void	print_results(t_ps *data, int mode)
{
	if (has_verbose_mode(mode))
		ft_printf("\n🏁 Sorting Complete!\n");
	if (has_verbose_mode(mode))
	{
		ft_printf("📊 Pre-optimization: %d operations\n", data->op_count);
		ft_printf("🔧 Running post-processing optimizations...\n");
	}
	post_sort_optimization(data);
	if (has_stats_mode(mode))
		display_operation_stats(data);
	if (has_verbose_mode(mode))
		ft_printf("\n📋 Operations List:\n");
	if (!has_debug_mode(mode))
		print_operations(data->op_list);
}
