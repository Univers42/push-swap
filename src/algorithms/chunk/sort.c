/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:08:29 by ugerkens          #+#    #+#             */
/*   Updated: 2025/07/18 16:26:00 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

void	sort(t_ps *data)
{
	t_chunk	to_sort;
	int		total_size;

	total_size = get_stack_size(&data->a);
	if (total_size <= 3)
	{
		if (total_size == 3)
			sort_three_simple(data);
		else if (total_size == 2)
		{
			if (get_items(&data->a, 1)
				> get_items(&data->a, 2))
				sa(data);
		}
		return ;
	}
	if (is_stack_sorted(data))
		return ;
	to_sort.loc = TOP_A;
	to_sort.size = total_size;
	rec_chunk_sort(data, &to_sort);
}
