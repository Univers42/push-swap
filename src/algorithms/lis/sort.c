/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 01:46:31 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/22 01:46:33 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

void	lis_sort(t_ps *data)
{
	if (!data || get_stack_size(&data->a) <= 3)
	{
		lis_handle_small_arrays(data);
		return ;
	}
	if (is_stack_sorted(data))
		return ;
	greedy_sort(data);
}
