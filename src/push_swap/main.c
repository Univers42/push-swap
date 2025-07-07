/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 23:22:18 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 23:22:20 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "debugger.h"

#ifndef MODE
# define MODE MODE_DEFAULT
#endif

static void	main_process_sorting(t_ps *data, int current_mode);

int	main(int argc, char *argv[])
{
	t_ps		data;
	int			current_mode;

	ft_memset(&data, 0, sizeof(t_ps));
	current_mode = MODE;
	debug_init(current_mode);
	initialize_push_swap_data(&data, argc, argv);
	main_process_sorting(&data, current_mode);
	release_allocated_memory(&data);
	exit(EXIT_SUCCESS);
}

static void	main_process_sorting(t_ps *data, int current_mode)
{
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
