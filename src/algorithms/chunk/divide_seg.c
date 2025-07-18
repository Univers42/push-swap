/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_seg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:57:19 by ugerkens          #+#    #+#             */
/*   Updated: 2025/07/19 00:35:57 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

static void	innit_size(t_chunk *min, t_chunk *mid, t_chunk *max);
static void	set_split_loc(t_loc loc, t_chunk *min, t_chunk *mid, t_chunk *max);
static void	set_third_pivots(t_loc loc, int crt_size, int *pivot_1,
				int *pivot_2);

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
			dest->max.size += transfer_chunk(data, to_split->loc, dest->max.loc);
			adjust_chunk(data, &dest->max);
			if (is_seg_sorted(data, 1) && to_split->size)
				fast_sort(data, to_split);
		}
		else if (next_value > max_value - pivot_1)
			dest->mid.size += transfer_chunk(data, to_split->loc, dest->mid.loc);
		else
			dest->min.size += transfer_chunk(data, to_split->loc, dest->min.loc);
	}
}

static void	innit_size(t_chunk *min, t_chunk *mid, t_chunk *max)
{
	min->size = 0;
	mid->size = 0;
	max->size = 0;
}

static void	set_split_loc(t_loc loc, t_chunk *min, t_chunk *mid, t_chunk *max)
{
	const t_chunk_fsm	*fsm = &get_chunk_fsm_table()[loc];

	min->loc = fsm->locs.min;
	mid->loc = fsm->locs.mid;
	max->loc = fsm->locs.max;
}

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
