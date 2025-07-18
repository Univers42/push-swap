/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 22:31:34 by codespace         #+#    #+#             */
/*   Updated: 2025/07/18 16:26:00 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

void	queue_sort(t_ps *data)
{
	if (!data || get_stack_size(&data->a) <= 3)
	{
		if (get_stack_size(&data->a) == 3)
			sort_three_simple(data);
		else if (get_stack_size(&data->a) == 2
			&& get_items(&data->a, 1)
			> get_items(&data->a, 2))
			sa(data);
		return ;
	}
	if (is_stack_sorted(data))
		return ;
	greedy_sort(data);
}
