/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_rotation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:51:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 16:03:33 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	lis_rotate_to_position(t_ps *data, int min_pos, int size_a);
static int	lis_find_min_position_in_stack(t_ps *data, int size_a,
				int min_value);

void	lis_final_rotation_to_sorted(t_ps *data)
{
	int	min_value;
	int	min_pos;
	int	size_a;

	if (verify_stack_is_sorted(data))
		return ;
	size_a = get_current_stack_size(&data->a);
	min_value = find_min_value_in_stack(&data->a);
	min_pos = lis_find_min_position_in_stack(data, size_a, min_value);
	if (min_pos == 0)
		return ;
	lis_rotate_to_position(data, min_pos, size_a);
	if (is_verbose_mode_enabled())
		lis_verify_final_rotation(data);
}

static void	lis_rotate_to_position(t_ps *data, int min_pos, int size_a)
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

static int	lis_find_min_position_in_stack(t_ps *data, int size_a,
					int min_value)
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
		current_index = calculate_next_down_index(&data->a, current_index);
		i++;
	}
	return (min_pos);
}
