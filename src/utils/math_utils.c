/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 23:15:36 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	k_sort_debug_last_elements(t_ps *data, int total_size);
static void	k_sort_check_ascending_order(t_ps *data, int total_size);


void	k_sort_verify_order(t_ps *data, int total_size)
{
	k_sort_debug_last_elements(data, total_size);
	k_sort_check_ascending_order(data, total_size);
}

static void	k_sort_debug_last_elements(t_ps *data, int total_size)
{
	int	i;

	ft_printf("🔍 [K-SORT DEBUG] Last 10 elements: ");
	i = total_size - 9;
	while (i <= total_size)
	{
		if (i > 0)
			ft_printf("%d ", get_stack_element_at_position(&data->a, i));
		i++;
	}
	ft_printf("\n");
}

static void	k_sort_check_ascending_order(t_ps *data, int total_size)
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
			ft_printf("🔍 [K-SORT DEBUG] Order breaks at position %d: %d > %d\n",
				i, current, next);
			break ;
		}
		i++;
	}
	if (is_ascending)
		ft_printf("🔍 [K-SORT DEBUG] Elements are in ascending order!\n");
	else
		ft_printf("🔍 [K-SORT DEBUG] Elements are NOT in ascending order!\n");
}
