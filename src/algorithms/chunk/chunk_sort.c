/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:56:55 by ugerkens          #+#    #+#             */
/*   Updated: 2025/07/19 01:19:14 by dlesieur         ###   ########.fr       */
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
			if (get_items(&data->a, 1)
				> get_items(&data->a, 2))
				sa(data);
		}
		return ;
	}
	if (is_stack_sorted(data))
		return ;
	chunk_sort_loop(data, &data->algo_ctx.u_ctx.s_chunk.current_chunk);
}

/**
moving a chunk to the `top` of a stack in your implemmentation
(using loc_seg)
- it ensureas that the chunk we want to operate on is in a predictable,
accessible positions
(the top of stack A or B), makin further operations (like sorting, splitting,
or moving elements
easier and more efficient)
in the context of chunk_sort and sort_chunks, befre performming fast_sort
or splitting the  chunk
we want the chnk to be at the top we can apply sortingoperation directl
 or split it cleanly into sub_chunks
@param data
@param to_sort
@return 
*/

static void	push_chunk(t_chunk_stack *stack, t_chunk chunk)
{
	if (stack->top < 1024)
		stack->chunks[stack->top++] = chunk;
}

static int	pop_chunk(t_chunk_stack *stack, t_chunk *out)
{
	if (stack->top > 0)
	{
		*out = stack->chunks[--stack->top];
		return (1);
	}
	return (0);
}

void	chunk_sort_loop(t_ps *data, t_chunk *to_sort)
{
	t_chunk_stack	stack;
	t_split_dest	dest;
	t_chunk			current;

	stack.top = 0;
	push_chunk(&stack, *to_sort);
	while (pop_chunk(&stack, &current))
	{
		(loc_seg(data, &current), fast_sort(data, &current));
		if (current.size <= 3)
		{
			if (current.size == 3)
				sort_three(data, &current);
			else if (current.size == 2)
				sort_two(data, &current);
			else if (current.size == 1)
				sort_one(data, &current);
			continue ;
		}
		divide_seg(data, &current, &dest);
		push_chunk(&stack, dest.min);
		push_chunk(&stack, dest.mid);
		push_chunk(&stack, dest.max);
	}
}
