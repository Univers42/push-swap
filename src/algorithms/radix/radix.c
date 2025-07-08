/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 23:45:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 22:57:35 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
# include "algorithms.h"
static void	radix_sort_by_bit_corrected(t_ps *data, int bit_position);
static void	radix_final_rotation_simple(t_ps *data);
static int	radix_find_min_position(t_ps *data, int size_a);
static void	radix_process_all_bits(t_ps *data, int total_size);

void	radix_sort(t_ps *data)
{
	int	total_size;

	if (!data || get_current_stack_size(&data->a) <= 3)
	{
		radix_handle_small_arrays(data);
		return ;
	}
	if (verify_stack_is_sorted(data))
		return ;
	total_size = get_current_stack_size(&data->a);
	radix_process_all_bits(data, total_size);
	radix_final_rotation_simple(data);
}

static void	radix_process_all_bits(t_ps *data, int total_size)
{
	int	max_bits;
	int	bit_position;

	max_bits = calculate_max_bits_for_size(total_size);
	bit_position = 0;
	while (bit_position < max_bits)
	{
		radix_sort_by_bit_corrected(data, bit_position);
		bit_position++;
	}
}

static void	radix_sort_by_bit_corrected(t_ps *data, int bit_position)
{
	int	total_elements;
	int	processed;
	int	current_element;
	int	zero_based_value;

	total_elements = get_current_stack_size(&data->a);
	processed = 0;
	while (processed < total_elements)
	{
		current_element = data->a.stack[data->a.top];
		zero_based_value = current_element - 1;
		if ((zero_based_value & (1 << bit_position)) == 0)
			pb(data);
		else
			ra(data);
		processed++;
	}
	while (get_current_stack_size(&data->b) > 0)
		pa(data);
}

static void	radix_final_rotation_simple(t_ps *data)
{
	int	min_pos;
	int	size_a;

	if (data->a.stack[data->a.top] == 1)
		return ;
	size_a = data->a.element_count;
	min_pos = radix_find_min_position(data, size_a);
	radix_rotate_to_position(data, min_pos, size_a);
}

static int	radix_find_min_position(t_ps *data, int size_a)
{
	int	min_pos;
	int	current_index;
	int	i;

	min_pos = 0;
	current_index = data->a.top;
	i = 0;
	while (i < size_a)
	{
		if (data->a.stack[current_index] == 1)
		{
			min_pos = i;
			break ;
		}
		current_index = (current_index + 1) % data->a.capacity;
		i++;
	}
	return (min_pos);
}
