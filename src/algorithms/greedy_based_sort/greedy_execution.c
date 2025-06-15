/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:41:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 22:57:36 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotation_a(t_ps *data, int moves_a, bool rotate_a_up);
static void	rotation_b(t_ps *data, int moves_b, bool rotate_b_up);

void	greedy_execute_move(t_ps *data, t_greedy_node *node)
{
	int		moves_a;
	int		moves_b;

	moves_a = node->cost_a;
	moves_b = node->cost_b;
	greedy_execute_combined_and_remaining(data, moves_a, moves_b, node);
	pa(data);
}

static void	rotation_a(t_ps *data, int moves_a, bool rotate_a_up)
{
	while (moves_a > 0)
	{
		if (rotate_a_up)
			ra(data);
		else
			rra(data);
		moves_a--;
	}
}

static void	rotation_b(t_ps *data, int moves_b, bool rotate_b_up)
{
	while (moves_b > 0)
	{
		if (rotate_b_up)
			rb(data);
		else
			rrb(data);
		moves_b--;
	}
}

void	greedy_execute_combined_and_remaining(t_ps *data, int moves_a,
		int moves_b, t_greedy_node *node)
{
	int		size_a;
	int		size_b;
	bool	rotate_a_up;
	bool	rotate_b_up;

	size_a = get_current_stack_size(&data->a);
	size_b = get_current_stack_size(&data->b);
	rotate_a_up = (node->target_pos <= size_a / 2);
	rotate_b_up = (node->index <= size_b / 2);
	while (moves_a > 0 && moves_b > 0 && rotate_a_up == rotate_b_up)
	{
		if (rotate_a_up)
			rr(data);
		else
			rrr(data);
		moves_a--;
		moves_b--;
	}
	rotation_a(data, moves_a, rotate_a_up);
	rotation_b(data, moves_b, rotate_b_up);
}

void	greedy_rotate_to_top(t_ps *data, int min_pos, int size_a)
{
	if (min_pos <= size_a / 2)
	{
		while (min_pos > 0)
		{
			ra(data);
			min_pos--;
		}
	}
	else
	{
		min_pos = size_a - min_pos;
		while (min_pos > 0)
		{
			rra(data);
			min_pos--;
		}
	}
}
