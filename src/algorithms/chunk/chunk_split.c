/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:57:19 by ugerkens          #+#    #+#             */
/*   Updated: 2025/07/19 00:14:44 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

static void	innit_size(t_chunk *min, t_chunk *mid, t_chunk *max);
static void	set_split_loc(t_loc loc, t_chunk *min, t_chunk *mid, t_chunk *max);
static void	set_third_pivots(t_loc loc, int crt_size, int *pivot_1,
				int *pivot_2);

void	chunk_split(t_ps *data, t_chunk *to_split, t_split_dest *dest)
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
			dest->max.size += move_from_to(data, to_split->loc, dest->max.loc);
			redox(data, &dest->max);
			if (a_partly_sort(data, 1) && to_split->size)
				easy_sort(data, to_split);
		}
		else if (next_value > max_value - pivot_1)
			dest->mid.size += move_from_to(data, to_split->loc, dest->mid.loc);
		else
			dest->min.size += move_from_to(data, to_split->loc, dest->min.loc);
	}
}

static void	innit_size(t_chunk *min, t_chunk *mid, t_chunk *max)
{
	min->size = 0;
	mid->size = 0;
	max->size = 0;
}

typedef struct s_chunk_locs {
	t_loc min;
	t_loc mid;
	t_loc max;
} t_chunk_locs;

typedef struct s_chunk_pivot_cfg {
	int pivot_1_factor;
	int pivot_2_factor;
	int pivot_1_override;
	int pivot_2_override;
	int pivot_1_min_size;
	int pivot_2_min_size;
} t_chunk_pivot_cfg;

typedef struct s_chunk_fsm {
	t_chunk_locs locs;
	t_chunk_pivot_cfg pivots;
} t_chunk_fsm;

// Mask function for FSM node initialization (4 parameters)
static t_chunk_fsm chunk_fsm_mask(
	t_chunk_locs locs,
	int pivot_1_factor,
	int pivot_2_factor,
	int pivot_overrides_and_mins[4])
{
	t_chunk_fsm fsm;
	fsm.locs = locs;
	fsm.pivots.pivot_1_factor = pivot_1_factor;
	fsm.pivots.pivot_2_factor = pivot_2_factor;
	fsm.pivots.pivot_1_override = pivot_overrides_and_mins[0];
	fsm.pivots.pivot_2_override = pivot_overrides_and_mins[1];
	fsm.pivots.pivot_1_min_size = pivot_overrides_and_mins[2];
	fsm.pivots.pivot_2_min_size = pivot_overrides_and_mins[3];
	return fsm;
}

// Singleton accessor for FSM table using mask and runtime initialization
static const t_chunk_fsm *get_chunk_fsm_table(void)
{
	static t_chunk_fsm table[4];
	static int initialized = 0;
	if (!initialized)
	{
		int top_a_cfg[4]     = {1, 0, 15, 0};
		int bottom_a_cfg[4]  = {1, 0, 15, 0};
		int top_b_cfg[4]     = {0, 0, 0, 0};
		int bottom_b_cfg[4]  = {0, 1, 0, 8};

		table[TOP_A] = chunk_fsm_mask(
			(t_chunk_locs){BOTTOM_B, TOP_B, BOTTOM_A},
			2, 1, top_a_cfg);
		table[BOTTOM_A] = chunk_fsm_mask(
			(t_chunk_locs){BOTTOM_B, TOP_B, TOP_A},
			2, 1, bottom_a_cfg);
		table[TOP_B] = chunk_fsm_mask(
			(t_chunk_locs){BOTTOM_B, BOTTOM_A, TOP_A},
			1, 1, top_b_cfg);
		table[BOTTOM_B] = chunk_fsm_mask(
			(t_chunk_locs){TOP_B, BOTTOM_A, TOP_A},
			1, 2, bottom_b_cfg);
		initialized = 1;
	}
	return table;
}

static void	set_split_loc(t_loc loc, t_chunk *min, t_chunk *mid, t_chunk *max)
{
	const t_chunk_fsm *fsm = &get_chunk_fsm_table()[loc];
	min->loc = fsm->locs.min;
	mid->loc = fsm->locs.mid;
	max->loc = fsm->locs.max;
}

static void	set_third_pivots(t_loc loc, int crt_size, int *pivot_1, int *pivot_2)
{
	const t_chunk_fsm *fsm = &get_chunk_fsm_table()[loc];

	int base_pivot_2;
	int base_pivot_1;

	// Calculate base pivots
	if (fsm->pivots.pivot_2_factor == 2)
		base_pivot_2 = crt_size / 2;
	else
		base_pivot_2 = crt_size / 3;

	if (fsm->pivots.pivot_1_factor == 2)
		base_pivot_1 = 2 * crt_size / 3;
	else
		base_pivot_1 = crt_size / 2;

	// Apply overrides if needed
	if (fsm->pivots.pivot_1_override && crt_size < fsm->pivots.pivot_1_min_size)
		base_pivot_1 = crt_size;

	if (fsm->pivots.pivot_2_override && crt_size < fsm->pivots.pivot_2_min_size)
		base_pivot_2 = crt_size / 2;

	*pivot_2 = base_pivot_2;
	*pivot_1 = base_pivot_1;
}
