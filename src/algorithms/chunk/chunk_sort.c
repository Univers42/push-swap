/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:56:55 by ugerkens          #+#    #+#             */
/*   Updated: 2025/07/17 01:39:48 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

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
	rec_chunk_sort(data, &data->algo_ctx.u_ctx.s_chunk.current_chunk);
}

/**
moving a chunk to the `top` of a stack in your implemmentation
(using chunk_to_the_top)
- it ensureas that the chunk we want to operate on is in a predictable,
accessible positions
(the top of stack A or B), makin further operations (like sorting, splitting,
or moving elements
easier and more efficient)
in the context of chunk_sort and rec_chunk_sort, befre performming easy_sort
or splitting the  chunk
we want the chnk to be at the top we can apply sortingoperation directl
 or split it cleanly into sub_chunks
@param data
@param to_sort
@return 
*/
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
