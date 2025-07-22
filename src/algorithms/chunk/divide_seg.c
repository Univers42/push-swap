/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_seg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 01:45:20 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/22 04:36:38 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

static void	innit_size(t_chunk *min, t_chunk *mid, t_chunk *max);
static void	set_split_loc(t_loc loc, t_chunk *min, t_chunk *mid, t_chunk *max);
static void	set_third_pivots(t_loc loc, int crt_size, int *pivot_1,
				int *pivot_2);

/**
 * @brief Splits a chunk into three subchunks using two pivots.
 *
 * This function is the core of the chunk splitting logic. It divides the
 * chunk pointed to by `to_split` into three subchunks (min, mid, max) based
 * on two pivot values. Each element is compared to the pivots and migrated
 * to the appropriate subchunk/location using mig_chunk.
 *
 * Example:
 *   Suppose chunk = [15, 3, 22, 8, 25, 1, 18], size=7, loc=TOP_A
 *   - max_value = 25
 *   - pivots: pivot_1 = 14, pivot_2 = 7
 *   - For each value:
 *       > max_value - pivot_2 (18): goes to max
 *       > max_value - pivot_1 (11): goes to mid
 *       else: goes to min
 *   - After loop, dest->max, dest->mid, dest->min have updated sizes/locations
 *
 * Importance: This is a core logic function for chunk_sort_loop, enabling
 * recursive partitioning of the stack into smaller, more sortable chunks.
 *
 * @param data     The push_swap context.
 * @param to_split The chunk to split.
 * @param dest     Output: the resulting subchunks (min, mid, max).
 */
void	divide_seg(t_ps *data, t_chunk *to_split, t_split_dest *dest)
{
	int	pivot_1;
	int	pivot_2;
	int	max_value;
	int	next_value;

	innit_size(&dest->min, &dest->mid, &dest->max);
	set_split_loc(to_split->loc, &dest->min, &dest->mid, &dest->max);
	set_third_pivots(to_split->loc, to_split->size, &pivot_1, &pivot_2);
	max_value = chunk_max_value(data, to_split);
	while (to_split->size--)
	{
		next_value = chunk_value(data, to_split, 1);
		if (next_value > max_value - pivot_2)
		{
			dest->max.size += mig_chunk(data, to_split->loc, dest->max.loc);
			adjust_chunk(data, &dest->max);
			if (is_seg_sorted(data, 1) && to_split->size)
				fast_sort(data, to_split);
		}
		else if (next_value > max_value - pivot_1)
			dest->mid.size += mig_chunk(data, to_split->loc, dest->mid.loc);
		else
			dest->min.size += mig_chunk(data, to_split->loc, dest->min.loc);
	}
}

/**
 * @brief Initializes the sizes of min, mid, and max chunks to zero.
 *
 * Helper for divide_seg.
 */
static void	innit_size(t_chunk *min, t_chunk *mid, t_chunk *max)
{
	min->size = 0;
	mid->size = 0;
	max->size = 0;
}

/**
 * @brief Sets the locations for the min, mid, and max subchunks based on FSM.
 *
 * Helper for divide_seg. Uses the chunk FSM table to determine where each
 * subchunk should be placed (e.g., TOP_A, BOTTOM_B, etc).
 */
static void	set_split_loc(t_loc loc, t_chunk *min, t_chunk *mid, t_chunk *max)
{
	const t_chunk_fsm	*fsm = &get_chunk_fsm_table()[loc];

	min->loc = fsm->locs.min;
	mid->loc = fsm->locs.mid;
	max->loc = fsm->locs.max;
}

/**
 * Part of partitionning algorithm above
 * @brief Calculates the two pivot values for splitting a chunk.
 * base calculation
 * pivot are fract(size) = (1/2 | 1/3 || 2/3 | 1/2)
 * override mechanism: If the current size is below certain thresholds, 
 * pivots are get adjusted:
 * `pivot 1` override sets it to the full size
 * `pivot 2` override sets it to half the size
 * The function also adapts pivot placement based on
 * placeholder data size, likely to optimize performance
 * for small vs. large datasets
 */
static void	set_third_pivots(t_loc loc, int crt_size, int *pivot_1,
								int *pivot_2)
{
	const t_chunk_fsm	*fsm = &get_chunk_fsm_table()[loc];
	int					base_pivot_2;
	int					base_pivot_1;

	if (fsm->pivots.pivot_2_factor == 2)
		base_pivot_2 = crt_size / 2;
	else
		base_pivot_2 = crt_size / 3;
	if (fsm->pivots.pivot_1_factor == 2)
		base_pivot_1 = 2 * crt_size / 3;
	else
		base_pivot_1 = crt_size / 2;
	if (fsm->pivots.pivot_1_override && crt_size < fsm->pivots.pivot_1_min_size)
		base_pivot_1 = crt_size;
	if (fsm->pivots.pivot_2_override && crt_size < fsm->pivots.pivot_2_min_size)
		base_pivot_2 = crt_size / 2;
	*pivot_2 = base_pivot_2;
	*pivot_1 = base_pivot_1;
}
