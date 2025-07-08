/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_based_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:56:55 by ugerkens          #+#    #+#             */
/*   Updated: 2025/06/16 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	chunk_sort(t_ps *data)
{
	if (data->total_size <= 3)
	{
		if (data->total_size == 3)
			sort_three_simple(data);
		else if (data->total_size == 2)
		{
			if (get_stack_element_at_position(&data->a, 1)
				> get_stack_element_at_position(&data->a, 2))
				sa(data);
		}
		return ;
	}
	if (verify_stack_is_sorted(data))
		return ;
	rec_chunk_sort(data, &data->algo.ctx.chunk.current_chunk);
}

void	rec_chunk_sort(t_ps *data, t_chunk *to_sort)
{
	t_split_dest	dest;

	chunk_to_the_top(data, to_sort);
	easy_sort(data, to_sort);
	if (to_sort->size <= 3)
	{
		if (to_sort->size == 3)
			sort_three(data, to_sort);
		else if (to_sort->size == 2)
			sort_two(data, to_sort);
		else if (to_sort->size == 1)
			sort_one(data, to_sort);
		return ;
	}
	chunk_split(data, to_sort, &dest);
	rec_chunk_sort(data, &dest.max);
	rec_chunk_sort(data, &dest.mid);
	rec_chunk_sort(data, &dest.min);
}

void	sort_two(t_ps *data, t_chunk *to_sort)
{
	if (to_sort->loc == BOTTOM_A || to_sort->loc == BOTTOM_B
		|| to_sort->loc == TOP_B)
	{
		move_from_to(data, to_sort->loc, TOP_A);
		move_from_to(data, to_sort->loc, TOP_A);
	}
	if (get_stack_element_at_position(&data->a, 1)
		> get_stack_element_at_position(&data->a, 2))
		sa(data);
	to_sort->size -= 2;
}

void	sort_one(t_ps *data, t_chunk *to_sort)
{
	if (to_sort->loc == BOTTOM_A || to_sort->loc == BOTTOM_B
		|| to_sort->loc == TOP_B)
		move_from_to(data, to_sort->loc, TOP_A);
	to_sort->size -= 1;
}
