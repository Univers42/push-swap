/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 23:22:18 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#ifndef ALGORITHM
# define ALGORITHM ALGO_CHUNK
#endif

int	main(int argc, char *argv[])
{
	t_ps	data;

	ft_memset(&data, 0, sizeof(t_ps));
	initialize_push_swap_data(&data, argc, argv);
	data.total_size = get_current_stack_size(&data.a);
	
	if (!verify_stack_is_sorted(&data))
	{
		select_algorithm(&data, ALGORITHM);
		execute_algorithm(&data);
		post_sort_optimization(&data);
		print_operations(data.op_list);
	}
	
	release_allocated_memory(&data);
	return (0);
}
	const char	*sorted_status;

	if (has_debug_mode(current_mode))
	{
		ft_printf("🚀 Starting Push Swap...\n");
		if (verify_stack_is_sorted(data))
			sorted_status = "✅ YES";
		else
			sorted_status = "❌ NO";
		ft_printf("📈 Initial state - Stack A size: %d, Is sorted: %s\n",
			get_current_stack_size(&data->a), sorted_status);
		print_algorithm_name(current_mode);
	}
	execute_selected_algorithm(data, current_mode);
	print_results(data, current_mode);
}
