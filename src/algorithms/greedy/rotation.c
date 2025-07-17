/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 09:12:12 by codespace         #+#    #+#             */
/*   Updated: 2025/07/17 09:25:16 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

void	rotate_to_top(t_ps *data, int min_pos, int size_a)
{
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
		min_pos = size_a - min_pos;
		while (min_pos > 0)
		{
			rra(data);
			min_pos--;
		}
	}
}

void	rotation_a(t_ps *data, int moves_a, bool rotate_a_up)
{
	while (moves_a > 0)
	{
		if (rotate_a_up)
			ra(data);
		else
			rra(data);
		moves_a--;
	}
}

void	rotation_b(t_ps *data, int moves_b, bool rotate_b_up)
{
	while (moves_b > 0)
	{
		if (rotate_b_up)
			rb(data);
		else
			rrb(data);
		moves_b--;
	}
}

void	final_rotation(t_ps *data)
{
	int	min_value;
	int	min_pos;
	int	size_a;

	min_value = find_min_value_in_stack(&data->a);
	min_pos = 0;
	size_a = get_current_stack_size(&data->a);
	min_pos = find_min_pos(data, size_a, min_value);
	rotate_to_top(data, min_pos, size_a);
}
