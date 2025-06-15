/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_sort_final.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 22:57:33 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	k_sort_apply_final_rotation(t_ps *data)
{
	int	min_value;
	int	min_pos;
	int	size_a;

	min_value = find_min_value_in_stack(&data->a);
	size_a = get_current_stack_size(&data->a);
	min_pos = k_find_min_position(data, size_a, min_value);
	if (min_pos == 0)
		return ;
	k_rotate_min_to_top(data, min_pos, size_a);
}
