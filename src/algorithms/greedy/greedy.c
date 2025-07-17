/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:52:32 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/17 09:23:51 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"


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
	push_to_b(data);
	data->algo_ctx.u_ctx.s_greedy.phase = 1;
	push_back_to_a(data);
	final_rotation(data);
}

