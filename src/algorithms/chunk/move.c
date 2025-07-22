/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 01:45:27 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/22 02:28:03 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

static void	move_top_a(t_ps *data, t_loc to);
static void	move_top_b(t_ps *data, t_loc to);
static void	move_bottom_a(t_ps *data, t_loc to);
static void	move_bottom_b(t_ps *data, t_loc to);

/**
 * @brief Returns the move function table (singleton).
 *
 * This jump table maps each t_loc (TOP_A, TOP_B, BOTTOM_A, BOTTOM_B)
 * to the corresponding move function for chunk migration.
 *
 * Example:
 *   get_move_table()[TOP_A] == &move_top_a
 *
 * Importance: Core helper for mig_chunk and chunk migration logic.
 */
t_move_func	*get_move_table(void)
{
	static t_move_func	table[4];
	static int			initialized = 0;

	if (!initialized)
	{
		table[0] = &move_top_a;
		table[1] = &move_top_b;
		table[2] = &move_bottom_a;
		table[3] = &move_bottom_b;
		initialized = 1;
	}
	return (table);
}

/**
 * @brief Moves the top of stack A to the specified location.
 *
 * - to == TOP_B: pb (push top of A to top of B)
 * - to == BOTTOM_A: ra (rotate A up, top becomes bottom)
 * - to == BOTTOM_B: pb + rb (push top of A to B, then rotate B)
 *
 * Example:
 *   move_top_a(data, TOP_B) // pb
 *   move_top_a(data, BOTTOM_A) // ra
 *   move_top_a(data, BOTTOM_B) // pb, rb
 */
static void	move_top_a(t_ps *data, t_loc to)
{
	if (to == TOP_B)
		pb(data);
	else if (to == BOTTOM_A)
		ra(data);
	else if (to == BOTTOM_B)
		(pb(data), rb(data));
}

/**
 * @brief Moves the top of stack B to the specified location.
 *
 * - to == TOP_A: pa (push top of B to top of A)
 * - to == BOTTOM_B: rb (rotate B up)
 * - to == BOTTOM_A: pa + ra (push B to A, then rotate A)
 *
 * Example:
 *   move_top_b(data, TOP_A) // pa
 *   move_top_b(data, BOTTOM_B) // rb
 *   move_top_b(data, BOTTOM_A) // pa, ra
 */
static void	move_top_b(t_ps *data, t_loc to)
{
	if (to == TOP_A)
		pa(data);
	else if (to == BOTTOM_B)
		rb(data);
	else if (to == BOTTOM_A)
		(pa(data), ra(data));
}

/**
 * @brief Moves the bottom of stack A to the specified location.
 *
 * - to == TOP_A: rra (reverse rotate A, bottom becomes top)
 * - to == TOP_B: rra + pb (reverse rotate A, then push to B)
 * - to == BOTTOM_B: rra + pb + rb (reverse rotate A, push to B, rotate B)
 *
 * Example:
 *   move_bottom_a(data, TOP_A) // rra
 *   move_bottom_a(data, TOP_B) // rra, pb
 *   move_bottom_a(data, BOTTOM_B) // rra, pb, rb
 */
static void	move_bottom_a(t_ps *data, t_loc to)
{
	if (to == TOP_A)
		rra(data);
	else if (to == TOP_B)
		(rra(data), pb(data));
	else if (to == BOTTOM_B)
		(rra(data), pb(data), rb(data));
}

/**
 * @brief Moves the bottom of stack B to the specified location.
 *
 * - to == TOP_B: rrb (reverse rotate B)
 * - to == TOP_A: rrb + pa (reverse rotate B, then push to A)
 * - to == BOTTOM_A: rrb + pa + ra (reverse rotate B, push to A, rotate A)
 *
 * Example:
 *   move_bottom_b(data, TOP_B) // rrb
 *   move_bottom_b(data, TOP_A) // rrb, pa
 *   move_bottom_b(data, BOTTOM_A) // rrb, pa, ra
 */
static void	move_bottom_b(t_ps *data, t_loc to)
{
	if (to == TOP_B)
		rrb(data);
	else if (to == TOP_A)
		(rrb(data), pa(data));
	else if (to == BOTTOM_A)
		(rrb(data), pa(data), ra(data));
}
