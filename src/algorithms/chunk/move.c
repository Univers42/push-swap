/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 00:57:12 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/19 01:10:32 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

typedef void (*move_func)(t_ps *data, t_loc to);

static void	move_top_a(t_ps *data, t_loc to);
static void	move_top_b(t_ps *data, t_loc to);
static void	move_bottom_a(t_ps *data, t_loc to);
static void	move_bottom_b(t_ps *data, t_loc to);

// Singleton accessor for jump table
static move_func *get_move_table(void)
{
	static move_func table[4];
	static int initialized = 0;
	if (!initialized)
	{
		table[0] = move_top_a;
		table[1] = move_top_b;
		table[2] = move_bottom_a;
		table[3] = move_bottom_b;
		initialized = 1;
	}
	return (table);
}

int	transfer_chunk(t_ps *data, t_loc from, t_loc to)
{
	if (from < 0 || from > 3)
		return (0);
	get_move_table()[from](data, to);
	return (1);
}

static void	move_top_a(t_ps *data, t_loc to)
{
	if (to == TOP_B)
		pb(data);
	else if (to == BOTTOM_A)
		ra(data);
	else if (to == BOTTOM_B)
		(pb(data), rb(data));
}

static void	move_top_b(t_ps *data, t_loc to)
{
	if (to == TOP_A)
		pa(data);
	else if (to == BOTTOM_B)
		rb(data);
	else if (to == BOTTOM_A)
		(pa(data), ra(data));
}

static void	move_bottom_a(t_ps *data, t_loc to)
{
	if (to == TOP_A)
		rra(data);
	else if (to == TOP_B)
		(rra(data), pb(data));
	else if (to == BOTTOM_B)
		(rra(data), pb(data), rb(data));
}

static void	move_bottom_b(t_ps *data, t_loc to)
{
	if (to == TOP_B)
		rrb(data);
	else if (to == TOP_A)
		(rrb(data), pa(data));
	else if (to == BOTTOM_A)
		(rrb(data), pa(data), ra(data));
}
