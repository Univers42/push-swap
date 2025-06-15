/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:41:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 15:43:43 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	radix_debug_final_verification(t_ps *data, int total_size)
{
	radix_debug_first_elements(data, total_size);
	radix_debug_check_order(data, total_size);
}

void	radix_debug_first_elements(t_ps *data, int total_size)
{
	int	i;

	ft_printf("🔍 [RADIX DEBUG] First 10 elements: ");
	i = 1;
	while (i <= 10 && i <= total_size)
	{
		ft_printf("%d ", get_stack_element_at_position(&data->a, i));
		i++;
	}
	ft_printf("\n");
}

void	radix_debug_check_order(t_ps *data, int total_size)
{
	int		i;
	bool	is_ascending;
	int		current;
	int		next;

	is_ascending = true;
	i = 1;
	while (i < total_size)
	{
		current = get_stack_element_at_position(&data->a, i);
		next = get_stack_element_at_position(&data->a, i + 1);
		if (current > next)
		{
			is_ascending = false;
			radix_debug_break_point(i, current, next);
			break ;
		}
		i++;
	}
	radix_debug_final_result(is_ascending);
}

void	radix_debug_break_point(int position, int current, int next)
{
	ft_printf("🔍 [RADIX DEBUG] Order breaks at position %d: %d > %d\n",
		position, current, next);
}

void	radix_debug_final_result(bool is_ascending)
{
	if (is_ascending)
		ft_printf("🔍 [RADIX DEBUG] Elements are in ascending order!\n");
	else
		ft_printf("🔍 [RADIX DEBUG] Elements are NOT in ascending order!\n");
}
