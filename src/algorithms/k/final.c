/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/18 16:23:33 by codespace        ###   ########.fr       */
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
