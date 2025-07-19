/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:30:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/19 03:22:45 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

void	k_sort_handle_small_arrays(t_ps *data)
{
	if (get_stack_size(&data->a) == 3)
		sort_three_simple(data);
	else if (get_stack_size(&data->a) == 2
		&& get_items(&data->a, 1)
		> get_items(&data->a, 2))
		sa(data);
}

void	k_sort_push_loop(t_ps *data, int *range, int *i, int target_remaining)
{
	int	current_element;
	int	rotations;
	int	total_size;

	total_size = get_stack_size(&data->a);
	rotations = 0;
	while (get_stack_size(&data->a) > target_remaining)
	{
		current_element = get_items(&data->a, 1);
		if (current_element > total_size - target_remaining)
		{
			ra(data);
			rotations++;
		}
		else if (current_element <= *i)
		{
			pb(data);
			if (get_stack_size(&data->b) > 1)
				rb(data);
			(*i)++;
			rotations = 0;
		}
		else
			k_handle_range_expansion(data, range, i, &rotations);
	}
}

void	k_handle_range_expansion(t_ps *data, int *range, int *i, int *rotations)
{
	int	current_element;
	int	total_size;

	total_size = get_stack_size(&data->a);
	current_element = get_items(&data->a, 1);
	if (current_element <= *i + *range)
	{
		pb(data);
		(*i)++;
		*rotations = 0;
	}
	else
	{
		ra(data);
		(*rotations)++;
		if (*rotations >= get_stack_size(&data->a))
		{
			*range += ft_sqrt(total_size) / 2;
			*rotations = 0;
		}
	}
}
