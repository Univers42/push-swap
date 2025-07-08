/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/08 18:53:17 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
# include "algorithms.h"

void	lis_sort(t_ps *data)
{
	if (!data || get_current_stack_size(&data->a) <= 3)
	{
		lis_handle_small_arrays(data);
		return ;
	}
	if (verify_stack_is_sorted(data))
		return ;
	
	// Simple LIS implementation - fallback to greedy for now
	// TODO: Implement proper LIS algorithm
	greedy_sort(data);
}