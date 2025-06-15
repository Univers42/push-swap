/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:40:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 22:57:36 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	radix_handle_small_arrays(t_ps *data)
{
	int	size;

	size = get_current_stack_size(&data->a);
	if (size == 3)
		sort_three_simple(data);
	else if (size == 2)
	{
		if (get_stack_element_at_position(&data->a, 1)
			> get_stack_element_at_position(&data->a, 2))
			sa(data);
	}
}

void	radix_debug_bit_pass(int bit_position)
{
	(void)bit_position;
}

void	radix_rotate_to_position(t_ps *data, int min_pos, int size_a)
{
	int	i;

	if (min_pos <= size_a / 2)
	{
		i = 0;
		while (i < min_pos)
		{
			ra(data);
			i++;
		}
	}
	else
	{
		i = 0;
		while (i < size_a - min_pos)
		{
			rra(data);
			i++;
		}
	}
}

int	calculate_max_bits_for_size(int size)
{
	int	bits;
	int	value;

	bits = 0;
	value = size - 1;
	while (value > 0)
	{
		value >>= 1;
		bits++;
	}
	return (bits);
}
