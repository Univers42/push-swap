/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:31:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/18 16:13:24 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	k_sort_handle_remaining_in_a(t_ps *data)
{
	if (get_stack_size(&data->a) == 3)
		sort_three_simple(data);
	else if (get_stack_size(&data->a) == 2
		&& get_items(&data->a, 1)
		> get_items(&data->a, 2))
		sa(data);
}

void	k_find_and_move_max_to_top(t_ps *data)
{
	int	max_value;
	int	max_position;
	int	size_b;

	max_value = 0;
	max_position = 0;
	size_b = get_stack_size(&data->b);
	k_find_max_in_stack_b(data, &max_value, &max_position, size_b);
	k_rotate_max_to_top_b(data, max_position, size_b);
}

void	k_find_max_in_stack_b(t_ps *data, int *max_value, int *max_position,
		int size_b)
{
	int	current_index;
	int	i;

	current_index = data->b.top;
	i = 0;
	while (i < size_b)
	{
		if (data->b.stack[current_index] > *max_value)
		{
			*max_value = data->b.stack[current_index];
			*max_position = i;
		}
		current_index = move_down(&data->b, current_index);
		i++;
	}
}

void	k_rotate_max_to_top_b(t_ps *data, int max_position, int size_b)
{
	int	reverse_rotations;

	if (max_position <= size_b / 2)
	{
		while (max_position > 0)
		{
			rb(data);
			max_position--;
		}
	}
	else
	{
		reverse_rotations = size_b - max_position;
		while (reverse_rotations > 0)
		{
			rrb(data);
			reverse_rotations--;
		}
	}
}

int	k_find_min_position(t_ps *data, int size_a, int min_value)
{
	int	current_index;
	int	min_pos;
	int	i;

	current_index = data->a.top;
	min_pos = 0;
	i = 0;
	while (i < size_a)
	{
		if (data->a.stack[current_index] == min_value)
		{
			min_pos = i;
			break ;
		}
		current_index = move_down(&data->a, current_index);
		i++;
	}
	return (min_pos);
}
