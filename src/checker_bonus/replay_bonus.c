/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replay_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/08 19:57:13 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

#if VISUALIZE == 1
# include "visualizer.h"

// Only define functions that are unique to replay functionality
void	replay_operations_from_input(t_ps *data)
{
	t_test_context *ctx = get_test_context();
	
	ft_printf("\n📼 Replaying %d recorded operations...\n", ctx->op_count);
	ft_printf("Press Enter to start visualization...\n");
	getchar();
	
	show_frame(data, "🏁 INITIAL STATE");
	
	t_operation *current = ctx->operations;
	int step = 1;
	
	while (current)
	{
		execute_operation_for_visual(data, current->name);
		
		char step_info[100];
		snprintf(step_info, sizeof(step_info), "Step %d: %s", step, current->name);
		show_frame(data, step_info);
		
		current = current->next;
		step++;
	}
	
	if (check_if_stack_is_empty(&data->b) && verify_stack_is_sorted(data))
		show_frame(data, "✅ SORTING COMPLETE - SUCCESS!");
	else
		show_frame(data, "❌ SORTING INCOMPLETE");
	
	ft_printf("\n📊 Visualization complete. Operations count: %d\n", ctx->op_count);
}

#else

void	replay_operations_from_input(t_ps *data)
{
	(void)data;
}

#endif
