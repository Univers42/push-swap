/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:40:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/18 16:13:24 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	radix_handle_small_arrays(t_ps *data)
{
	int	size;

	size = get_stack_size(&data->a);
	if (size == 3)
		sort_three_simple(data);
	else if (size == 2)
	{
		if (get_items(&data->a, 1)
			> get_items(&data->a, 2))
			sa(data);
	}
}

/**
 * This function is commune to the greedy sort, to do the finall rotation
 * we need to find the min value and pop it right to the top
 * of the staack from  size->a
 */
void	radix_rotate_to_position(t_ps *data, int min_pos, int size_a)
{
	int	i;
	int first_half;

	first_half = (min_pos <= size_a / 2);

	if (first_half)
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

/**
 * let's trace this functions with an example 
 * First iteration:: +1
 *	value = 5 (binary:: `101`) >>= 1 : (binary:: `10`)
 * Second iteration: + 2
 * value >>= 1 (binary:: `10`) : (binary:: `1`)
 * third itertion + 3
 * value >>= 1 (binary:: `1` ) :(binary:: `0`)
 * 0 the loop stops
 * 
 * Why we need this function ?
 * we need to know the number of bits required to represent
 * the largest index (size - 1) so we can determine how many bitwise
 * passes are needed in the radix sort algorithm
 * In radix sort
 * each pass sorts the numbers based on a single bit position (
 * from LSB TO MSB). The number of passes required is equal to
 * value . This ensures that every bit of every number
 * is considered
 * , so hthe sort is complete and correct for all possible vlaues
 * 
 * in the stack
 */
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
