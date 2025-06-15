/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:58:08 by ugerkens          #+#    #+#             */
/*   Updated: 2025/06/13 14:00:26 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	move_from_top_a(t_ps *data, t_loc to);
static void	move_from_top_b(t_ps *data, t_loc to);
static void	move_from_bottom_a(t_ps *data, t_loc to);
static void	move_from_bottom_b(t_ps *data, t_loc to);

int	move_from_to(t_ps *data, t_loc from, t_loc to)
{
	if (from == TOP_A)
		move_from_top_a(data, to);
	else if (from == TOP_B)
		move_from_top_b(data, to);
	else if (from == BOTTOM_A)
		move_from_bottom_a(data, to);
	else if (from == BOTTOM_B)
		move_from_bottom_b(data, to);
	return (1);
}

static void	move_from_top_a(t_ps *data, t_loc to)
{
	if (to == TOP_B)
		pb(data);
	else if (to == BOTTOM_A)
		ra(data);
	else if (to == BOTTOM_B)
	{
		pb(data);
		rb(data);
	}
}

static void	move_from_top_b(t_ps *data, t_loc to)
{
	if (to == TOP_A)
		pa(data);
	else if (to == BOTTOM_B)
		rb(data);
	else if (to == BOTTOM_A)
	{
		pa(data);
		ra(data);
	}
}

static void	move_from_bottom_a(t_ps *data, t_loc to)
{
	if (to == TOP_A)
		rra(data);
	else if (to == TOP_B)
	{
		rra(data);
		pb(data);
	}
	else if (to == BOTTOM_B)
	{
		rra(data);
		pb(data);
		rb(data);
	}
}

static void	move_from_bottom_b(t_ps *data, t_loc to)
{
	if (to == TOP_B)
		rrb(data);
	else if (to == TOP_A)
	{
		rrb(data);
		pa(data);
	}
	else if (to == BOTTOM_A)
	{
		rrb(data);
		pa(data);
		ra(data);
	}
}
