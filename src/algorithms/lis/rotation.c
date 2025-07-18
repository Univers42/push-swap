/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:51:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/18 16:26:00 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

static void	lis_rotate_to_position(t_ps *data, int min_pos, int size_a);
static int	lis_find_min_position_in_stack(t_ps *data, int size_a,
				int min_value);

void	lis_final_rotation_to_sorted(t_ps *data)
{
	int	min_value;
	int	min_pos;
	int	size_a;

	if (is_stack_sorted(data))
		return ;
	size_a = get_stack_size(&data->a);
	min_value = find_min(&data->a);
	min_pos = lis_find_min_position_in_stack(data, size_a, min_value);
	if (min_pos == 0)
		return ;
	lis_rotate_to_position(data, min_pos, size_a);
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
		current_index = move_down(&data->a, current_index);
		i++;
	}
	return (min_pos);
}
