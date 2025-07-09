/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 22:31:34 by codespace         #+#    #+#             */
/*   Updated: 2025/07/09 22:31:42 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

void	queue_sort(t_ps *data)
{
	if (!data || get_current_stack_size(&data->a) <= 3)
	{
		if (get_current_stack_size(&data->a) == 3)
			sort_three_simple(data);
		else if (get_current_stack_size(&data->a) == 2
			&& get_stack_element_at_position(&data->a, 1)
			> get_stack_element_at_position(&data->a, 2))
			sa(data);
		return ;
	}
	if (verify_stack_is_sorted(data))
		return ;
	greedy_sort(data);
}
