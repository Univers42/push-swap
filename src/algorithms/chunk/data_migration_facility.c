/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_migration_facility.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 01:45:16 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/22 04:35:15 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

/**
 * @brief Migrates (moves) a chunk from one location to another.
 *
 * This function is a helper for chunk splitting and migration. It uses a
 * function pointer table to select the correct move operation based on the
 * source location (`from`). The move operation (e.g., pb, pa, ra, rb, etc.)
 * is then called to move the chunk to the desired destination (`to`).
 *
 * Example:
 *   mig_chunk(data, TOP_A, TOP_B) 
 * ========= Moves top of stack A to top of stack B (pb)
 *   mig_chunk(data, BOTTOM_B, TOP_A)
 * ========= Moves bottom of stack B to top of stack A (rrb + pa)
 *
 * Importance: This is a core helper for divide_seg and chunk_sort_loop,
 * enabling flexible chunk movement between stack locations.
 *
 * @param data The push_swap context.
 * @param from The source location (enum t_loc).
 * @param to   The destination location (enum t_loc).
 * @return 1 if the move was performed, 0 if invalid.
 */
int	mig_chunk(t_ps *data, t_loc from, t_loc to)
{
	t_move_func	fn;

	if (from < 0 || from > 3)
		return (0);
	fn = get_move_table()[from];
	fn(data, to);
	return (1);
}
