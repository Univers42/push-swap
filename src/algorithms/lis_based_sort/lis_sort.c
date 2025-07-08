/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
# include "algorithms.h"
void	lis_sort(t_ps *data)
{
	int	total_size;

	if (!data || get_current_stack_size(&data->a) <= 3)
	{
		lis_handle_small_arrays(data);
		return ;
	}
	if (verify_stack_is_sorted(data))
		return ;
	total_size = get_current_stack_size(&data->a);
	if (total_size > 100)
		greedy_sort(data);
	else
		greedy_sort(data);
}