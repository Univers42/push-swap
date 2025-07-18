/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:42:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/18 16:23:33 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

/**
 * find_target_position - Finds the optimal target position in stack A for a value from B.
 * @data: Pointer to the main push_swap data structure.
 * @value: The value from stack B to insert.
 *
 * Returns the index in stack A where the value should be inserted to maintain order.
 * If no suitable position is found, returns the position of the minimum value.
 */
int	find_target_position(t_ps *data, int value)
{
	int	size_a;
	int	target_pos;

	size_a = get_stack_size(&data->a);
	target_pos = find_best_target(data, value, size_a);
	if (target_pos == -1)
		target_pos = find_min_target(data, size_a);
	return (target_pos);
}

/**
 * find_best_target - Finds the best position in A for a value, where the next greater element is.
 * @data: Pointer to the main push_swap data structure.
 * @value: The value to insert.
 * @size_a: Size of stack A.
 *
 * Returns the index of the smallest element in A that is greater than value.
 * If none found, returns -1
 * 
 * @note this loop look for the best target mmeanning that it will compare the 
 * current value to move into stack B to be moved into stack A
 * stack a = "{
 * [0] = 1},
 * {[1] = 3},
 * {[2] = 4}"
 * }"
 * stack B =  
 * {
 * [0] = 2,
 * [1]=5
 * }
 * 1. i = 0:
 * current_value = 1
 * 1 >2 ? No.
 * move to next
 * i = 1:
 * current_value = 3
 * 3 > 2 ? Yes.
 * 3 < INT_MAX ? yes
 * update :
 * - best_target = 3
 * - target_pos = 1
 * i = 2
 * current_valuue = 4
 * 4 > 2 ? yes
 * 4 < 3 No.
 * no update
 * 
 * the function return [1]
 * 
 * What does this means ?
 * The value 2 from B should be inserted at position 1 in A 
 * (after the first element, which is 1)
 * After insertion, A would be: 1,2,3,4 (still sorted)
 * 
 * for 5  we repeat the process
 *i = 0: Current_value = 1 -> 1> 5 ? NO
i = 1: Current_value = 3 -> 3 > 5 ? NO
i = 2: Current_value = 4 -> 4 > 5 ? NO
no suitable position found return  = -1
that means tehre are not number greater than it
so it should be inserted after the minimmum (which is 1,at position )
 */
int	find_best_target(t_ps *data, int value, int size_a)
{
	int	current_index;
	int	best_target;
	int	target_pos;
	int	current_value;
	int	i;

	current_index = data->a.top;
	best_target = INT_MAX;
	target_pos = -1;
	i = 0;
	while (i < size_a)
	{
		current_value = data->a.stack[current_index];
		if (current_value > value && current_value < best_target)
		{
			best_target = current_value;
			target_pos = i;
		}
		current_index = move_down(&data->a, current_index);
		i++;
	}
	return (target_pos);
}

/**
 * find_min_target - Finds the position of the minimum value in stack A.
 * @data: Pointer to the main push_swap data structure.
 * @size_a: Size of stack A.
 *
 * Returns the index of the minimum value in stack A.
 */
int	find_min_target(t_ps *data, int size_a)
{
	int	min_value;
	int	current_index;
	int	target_pos;
	int	i;

	min_value = find_min(&data->a);
	current_index = data->a.top;
	target_pos = 0;
	i = 0;
	while (i < size_a)
	{
		if (data->a.stack[current_index] == min_value)
		{
			target_pos = i;
			break ;
		}
		current_index = move_down(&data->a, current_index);
		i++;
	}
	return (target_pos);
}

/**
 * find_min_pos - Finds the position of a given minimum value in stack A.
 * @data: Pointer to the main push_swap data structure.
 * @size_a: Size of stack A.
 * @min_value: The minimum value to find.
 *
 * Returns the index of min_value in stack A.
 */
int	find_min_pos(t_ps *data, int size_a, int min_value)
{
	int	current_index;
	int	min_pos;
	int	i;

	current_index = data->a.top;
	min_pos = 0;
	i = 0;
	while (i < size_a)
	{
		if (data->a.stack[current_index] == min_value)
		{
			min_pos = i;
			break ;
		}
		current_index = move_down(&data->a, current_index);
		i++;
	}
	return (min_pos);
}

/**
 * find_cheapest - Finds the index of the node with the lowest total cost.
 * @nodes: Array of greedy nodes.
 * @size: Number of nodes.
 *
 * Returns the index of the node with the smallest total_cost.
 * Used to select the next optimal move.
 */
int	find_cheapest(t_greedy_node *nodes, int size)
{
	int	cheapest_idx;
	int	min_cost;
	int	i;

	cheapest_idx = 0;
	min_cost = nodes[0].total_cost;
	i = 1;
	while (i < size)
	{
		if (nodes[i].total_cost < min_cost)
		{
			min_cost = nodes[i].total_cost;
			cheapest_idx = i;
		}
		i++;
	}
	return (cheapest_idx);
}
