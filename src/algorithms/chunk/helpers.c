/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:31:22 by codespace         #+#    #+#             */
/*   Updated: 2025/07/19 00:55:07 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

/**
this function updates the location field (loc) of a t_chunk structure
(to_sort) ased on its current position and size in a push_swap stack.
if to_sort->loc is BOTTOM_B and the current size b equals to sort->size,
it set to_sort->loc to TOP_B and so on...

@note this is used to track if a chunk has been moved to the top oof
a stack,, based on its size and position
*/
void	loc_seg(t_ps *data, t_chunk *to_sort)
{
	if (to_sort->loc == BOTTOM_B
		&& get_stack_size(&data->b) == to_sort->size)
		to_sort->loc = TOP_B;
	if (to_sort->loc == BOTTOM_A
		&& get_stack_size(&data->a) == to_sort->size)
		to_sort->loc = TOP_A;
}

// Mask function for FSM node initialization (4 parameters)
static t_chunk_fsm	chunk_fsm_mask( t_chunk_locs locs, int pivot_1_factor,
									int pivot_2_factor,
									const int *pivot_overrides_and_mins)
{
	t_chunk_fsm	fsm;

	fsm.locs = locs;
	fsm.pivots.pivot_1_factor = pivot_1_factor;
	fsm.pivots.pivot_2_factor = pivot_2_factor;
	fsm.pivots.pivot_1_override = pivot_overrides_and_mins[0];
	fsm.pivots.pivot_2_override = pivot_overrides_and_mins[1];
	fsm.pivots.pivot_1_min_size = pivot_overrides_and_mins[2];
	fsm.pivots.pivot_2_min_size = pivot_overrides_and_mins[3];
	return (fsm);
}

// Singleton accessor for FSM table using mask and runtime initialization
const t_chunk_fsm	*get_chunk_fsm_table(void)
{
	static t_chunk_fsm	table[4];
	const int			matrix[4][4] = {
	{1, 0, 15, 0},
	{1, 0, 15, 0},
	{0, 0, 0, 0},
	{0, 1, 0, 8}
	};
	static int			initialized = 0;

	if (!initialized)
	{
		table[TOP_A] = chunk_fsm_mask((t_chunk_locs){BOTTOM_B, TOP_B, BOTTOM_A},
				2, 1, matrix[0]);
		table[BOTTOM_A] = chunk_fsm_mask(
				(t_chunk_locs){BOTTOM_B, TOP_B, TOP_A},
				2, 1, matrix[1]);
		table[TOP_B] = chunk_fsm_mask(
				(t_chunk_locs){BOTTOM_B, BOTTOM_A, TOP_A},
				1, 1, matrix[2]);
		table[BOTTOM_B] = chunk_fsm_mask(
				(t_chunk_locs){TOP_B, BOTTOM_A, TOP_A},
				1, 2, matrix[3]);
		initialized = 1;
	}
	return (table);
}

int	chunk_value(t_ps *data, t_chunk *chunk, int n)
{
	t_loc	loc;
	t_stack	*stk;
	int		i;

	loc = chunk->loc;
	stk = loc_to_stack(data, loc);
	i = 0;
	if (loc == TOP_A || loc == TOP_B)
		i = stk->top;
	else if (loc == BOTTOM_A || loc == BOTTOM_B)
		i = stk->bottom;
	if (loc == TOP_A || loc == TOP_B)
		while (--n > 0)
			i = move_down(stk, i);
	else if (loc == BOTTOM_A || loc == BOTTOM_B)
		while (--n > 0)
			i = move_up(stk, i);
	return (stk->stack[i]);
}

int	chunk_max_value(t_ps *data, t_chunk *chunk)
{
	t_stack	*stk;
	int		size;
	int		max_value;
	int		i;

	stk = loc_to_stack(data, chunk->loc);
	size = chunk->size;
	max_value = 0;
	i = 0;
	if (chunk->loc == TOP_A || chunk->loc == TOP_B)
		i = stk->top;
	else if (chunk->loc == BOTTOM_A || chunk->loc == BOTTOM_B)
		i = stk->bottom;
	while (size--)
	{
		if (stk->stack[i] > max_value)
			max_value = stk->stack[i];
		if (chunk->loc == TOP_A || chunk->loc == TOP_B)
			i = move_down(stk, i);
		else if (chunk->loc == BOTTOM_A || chunk->loc == BOTTOM_B)
			i = move_up(stk, i);
	}
	return (max_value);
}

t_stack	*loc_to_stack(t_ps *data, t_loc loc)
{
	if (loc == TOP_A || loc == BOTTOM_A)
		return (&data->a);
	else
		return (&data->b);
}
