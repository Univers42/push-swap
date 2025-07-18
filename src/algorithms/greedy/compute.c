/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 09:13:42 by codespace         #+#    #+#             */
/*   Updated: 2025/07/18 16:08:03 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

/**
 Computes the cost of moving a node from stack B to its target position in
 Stack A
 @node: pointer to the greey  node containing index and target position
 @size_a: Current size of Stack A
 @size_b: Current size of stack B

 this function calculates the nnumber of rotations (cost) needed in both
 stacks to brign the node to the top of stack B and its target positions to
 the top of Stack A. The cost is minimized by rotating up if the position is
 in the first halld,, or down otherwise

 Example:
  If node-->index == 1, size_b = 5, node->target_pos = 3, size_a = 6
  then cost_b = 1, cost_a = 3, and total_cost is calculated accordingly
*/
void	calculate_move_costs(t_greedy_node *node, int size_a, int size_b)
{
	if (node->index <= size_b / 2)
		node->cost_b = node->index;
	else
		node->cost_b = size_b - node->index;
	if (node->target_pos <= size_a / 2)
		node->cost_a = node->target_pos;
	else
		node->cost_a = size_a - node->target_pos;
	node->total_cost =  calculate_total_cost(node->cost_a, node->cost_b,
			node->target_pos, node->index);
}

/**
 * calculate_costs - Fills an array of greedy nodes with move costs for all elements in stack B.
 * @data: Pointer to the main push_swap data structure.
 * @nodes: Array of greedy nodes to fill.
 * @size_b: Number of elements in stack B.
 *
 * For each element in stack B, this function:
 *   - Sets its value and index.
 *   - Finds its target position in stack A.
 *   - Calculates the move costs using calculate_move_costs().
 * This prepares the nodes for cost-based selection of the next move.
 */
void	calculate_costs(t_ps *data, t_greedy_node *nodes, int size_b)
{
	int	size_a;
	int	current_index;
	int	i;

	size_a = get_stack_size(&data->a);
	current_index = data->b.top;
	i = 0;
	while (i < size_b)
	{
		nodes[i].value = data->b.stack[current_index];
		nodes[i].index = i;
		nodes[i].target_pos = find_target_position(data, nodes[i].value);
		calculate_move_costs(&nodes[i], size_a, size_b);
		current_index = move_down(&data->b, current_index);
		i++;
	}
}

/**
 * calculate_total_cost - Determines the total cost to move an element from B to A.
 * @cost_a: Rotations needed in stack A.
 * @cost_b: Rotations needed in stack B.
 * @pos_a: Target position in stack A.
 * @pos_b: Current index in stack B.
 *
 * If both stacks rotate in the same direction, the cost is the maximum of the two.
 * Otherwise, the cost is the sum.
 *
 * Example:
 *   If cost_a = 2, cost_b = 3, pos_a = 1, pos_b = 4, returns 5 if directions differ, else 3.
 */
int	calculate_total_cost(int cost_a, int cost_b, int pos_a, int pos_b)
{
	bool	rotate_a_up;
	bool	rotate_b_up;
	int		size_a;
	int		size_b;

	size_a = 100;
	size_b = 100;
	rotate_a_up = (pos_a <= size_a / 2);
	rotate_b_up = (pos_b <= size_b / 2);
	if (rotate_a_up == rotate_b_up)
	{
		if (cost_a > cost_b)
			return (cost_a);
		else
			return (cost_b);
	}
	return (cost_a + cost_b);
}
