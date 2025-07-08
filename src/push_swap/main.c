#include "push_swap.h"

// ...existing code...

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
	init_algorithm(data, current_mode);
	run_algorithm(data);
	print_results(data, current_mode);
}

// ...existing code...