/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:41:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/18 16:08:10 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

/**
 * execute_move - Executes the optimal move to bring a node from B to A.
 * @data: Pointer to the main push_swap data structure.
 * @node: The greedy node to move.
 *
 * This function performs the necessary rotations and push operation to move
 * the selected node from stack B to its target position in stack A.
 * It uses execute_combined_and_remaining() to optimize combined rotations.
 */
void	execute_move(t_ps *data, t_greedy_node *node)
{
	int		moves_a;
	int		moves_b;

	moves_a = node->cost_a;
	moves_b = node->cost_b;
	execute_combined_and_remaining(data, moves_a, moves_b, node);
	pa(data);
}

/**
 * execute_combined_and_remaining - Performs combined and remaining rotations for a move.
 * @data: Pointer to the main push_swap data structure.
 * @moves_a: Number of rotations needed in stack A.
 * @moves_b: Number of rotations needed in stack B.
 * @node: The greedy node being moved.
 *
 * This function first performs simultaneous rotations (rr or rrr) if both stacks
 * need to rotate in the same direction, then completes any remaining rotations
 * in each stack individually.
 *
 * Example:
 *   If both rotate up, does rr; if both down, does rrr; then finishes with ra/rra or rb/rrb.
 */
void	execute_combined_and_remaining(t_ps *data, int moves_a,
		int moves_b, t_greedy_node *node)
{
	int		size_a;
	int		size_b;
	bool	rotate_a_up;
	bool	rotate_b_up;

	size_a = get_stack_size(&data->a);
	size_b = get_stack_size(&data->b);
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
