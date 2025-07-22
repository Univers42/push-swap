/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 01:46:02 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/22 01:46:04 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	k_sort_apply_final_rotation(t_ps *data)
{
	int	min_value;
	int	min_pos;
	int	size_a;

	min_value = find_min(&data->a);
	size_a = get_stack_size(&data->a);
	min_pos = k_find_min_position(data, size_a, min_value);
	if (min_pos == 0)
		return ;
	k_rotate_min_to_top(data, min_pos, size_a);
}
