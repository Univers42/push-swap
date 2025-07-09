/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:50:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/09 22:30:10 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

static void	lis_find_and_move_max(t_ps *data);
static void	lis_find_max_in_stack_b(t_ps *data, int *max_value,
				int *max_position, int size_b);

void	lis_handle_small_arrays(t_ps *data)
{
	int	size;

	size = get_current_stack_size(&data->a);
	if (size == 3)
		sort_three_simple(data);
	else if (size == 2
		&& get_stack_element_at_position(&data->a, 1)
		> get_stack_element_at_position(&data->a, 2))
		sa(data);
}

void	lis_push_back_phase(t_ps *data)
{
	while (get_current_stack_size(&data->b) > 0)
	{
		lis_find_and_move_max(data);
		pa(data);
	}
}

static void	lis_find_and_move_max(t_ps *data)
{
	int	max_value;
	int	max_position;
	int	size_b;

	max_value = INT_MIN;
	max_position = 0;
	size_b = get_current_stack_size(&data->b);
	lis_find_max_in_stack_b(data, &max_value, &max_position, size_b);
	lis_rotate_max_to_top(data, max_position, size_b);
}

static void	lis_find_max_in_stack_b(t_ps *data, int *max_value,
		int *max_position, int size_b)
{
	int	current_index;
	int	j;

	current_index = data->b.top;
	j = 0;
	while (j < size_b)
	{
		if (data->b.stack[current_index] > *max_value)
		{
			*max_value = data->b.stack[current_index];
			*max_position = j;
		}
		current_index = calculate_next_down_index(&data->b, current_index);
		j++;
	}
}

void	lis_rotate_max_to_top(t_ps *data, int max_position, int size_b)
{
	int	j;

	if (max_position <= size_b / 2)
	{
		j = 0;
		while (j < max_position)
		{
			rb(data);
			j++;
		}
	}
	else
	{
		j = 0;
		while (j < size_b - max_position)
		{
			rrb(data);
			j++;
		}
	}
}
