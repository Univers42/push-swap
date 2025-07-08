/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_sort_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:32:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 16:14:16 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	k_rotate_min_to_top(t_ps *data, int min_pos, int size_a)
{
	int	reverse_rotations;

	if (min_pos <= size_a / 2)
	{
		while (min_pos > 0)
		{
			ra(data);
			min_pos--;
		}
	}
	else
	{
		reverse_rotations = size_a - min_pos;
		while (reverse_rotations > 0)
		{
			rra(data);
			reverse_rotations--;
		}
	}
}
