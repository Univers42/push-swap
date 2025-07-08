/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_operations_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

#if VISUALIZE == 1
# include "visualizer.h"
#endif

void	execute_checker_operation(t_ps *data, t_op operation)
{
#if VISUALIZE == 1
	char	step_info[100];
	static int step = 1;
	
	if (is_recording())
	{
		snprintf(step_info, sizeof(step_info), "Step %d: %s", 
			step++, op_to_string(operation));
	}
#endif
	
	if (operation == OP_PA)
		checker_push(&data->b, &data->a);
	else if (operation == OP_PB)
		checker_push(&data->a, &data->b);
	else if (operation == OP_SA)
		checker_swap(&data->a);
	else if (operation == OP_SB)
		checker_swap(&data->b);
	else if (operation == OP_SS)
	{
		checker_swap(&data->a);
		checker_swap(&data->b);
	}
	else if (operation == OP_RA)
		checker_rotate(&data->a);
	else if (operation == OP_RB)
		checker_rotate(&data->b);
	else if (operation == OP_RR)
	{
		checker_rotate(&data->a);
		checker_rotate(&data->b);
	}
	else if (operation == OP_RRA)
		checker_r_rotate(&data->a);
	else if (operation == OP_RRB)
		checker_r_rotate(&data->b);
	else if (operation == OP_RRR)
	{
		checker_r_rotate(&data->a);
		checker_r_rotate(&data->b);
	}
	
#if VISUALIZE == 1
	if (is_recording())
		show_frame(data, step_info);
#endif
}
		checker_r_rotate(&data->a);
	else if (operation == OP_RRB)
		checker_r_rotate(&data->b);
	else if (operation == OP_RRR)
	{
		checker_r_rotate(&data->a);
		checker_r_rotate(&data->b);
	}
}
