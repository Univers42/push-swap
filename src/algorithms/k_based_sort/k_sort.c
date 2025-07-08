/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_sort.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 23:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

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
	k_sort_main_process(data, total_size);
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
	while (get_current_stack_size(&data->b) > 0)
	{
		k_find_and_move_max_to_top(data);
		pa(data);
	}
	k_sort_apply_final_rotation(data);
}
