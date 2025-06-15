/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:10:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 15:58:19 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	lis_debug_first_elements(t_ps *data, int total_size)
{
	int	i;

	ft_printf("🔍 [LIS DEBUG] First 10 elements: ");
	i = 1;
	while (i <= 10 && i <= total_size)
	{
		ft_printf("%d ", get_stack_element_at_position(&data->a, i));
		i++;
	}
	ft_printf("\n");
}

void	lis_debug_check_order(t_ps *data, int total_size)
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
			ft_printf("🔍 [LIS DEBUG] Order breaks at position %d: %d > %d\n",
				i, current, next);
			break ;
		}
		i++;
	}
	lis_print_final_result(is_ascending);
}
