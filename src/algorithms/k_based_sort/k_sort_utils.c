/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_sort_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:30:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 23:15:57 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	k_sort_handle_small_arrays(t_ps *data)
{
	if (get_current_stack_size(&data->a) == 3)
		sort_three_simple(data);
	else if (get_current_stack_size(&data->a) == 2
		&& get_stack_element_at_position(&data->a, 1)
		> get_stack_element_at_position(&data->a, 2))
		sa(data);
}

void	k_sort_print_debug_info(t_ps *data, int total_size)
{
	int	i;

	ft_printf("🔍 [K-SORT DEBUG] First 10 elements: ");
	i = 1;
	while (i <= 10 && i <= total_size)
	{
		ft_printf("%d ", get_stack_element_at_position(&data->a, i));
		i++;
	}
	ft_printf("\n");
	k_sort_verify_order(data, total_size);
}

void	k_sort_push_loop(t_ps *data, int *range, int *i, int target_remaining)
{
	int	current_element;
	int	rotations;
	int	total_size;

	total_size = get_current_stack_size(&data->a);
	rotations = 0;
	while (get_current_stack_size(&data->a) > target_remaining)
	{
		current_element = get_stack_element_at_position(&data->a, 1);
		if (current_element > total_size - target_remaining)
		{
			ra(data);
			rotations++;
		}
		else if (current_element <= *i)
		{
			pb(data);
			if (get_current_stack_size(&data->b) > 1)
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

	total_size = get_current_stack_size(&data->a);
	current_element = get_stack_element_at_position(&data->a, 1);
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
		if (*rotations >= get_current_stack_size(&data->a))
		{
			*range += ft_sqrt(total_size) / 2;
			*rotations = 0;
		}
	}
}
