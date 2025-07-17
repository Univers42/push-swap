/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 09:12:12 by codespace         #+#    #+#             */
/*   Updated: 2025/07/17 12:17:07 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

/**
 * rotations element are really easy to understand they're just 
 * min_pos <= size_a / 2
 *  
 */

/**
 * rotate_to_top - Rotates stack A so the element at min_pos comes to the top.
 * @data: Pointer to the main push_swap data structure.
 * @min_pos: The position of the minimum value in A.
 * @size_a: Size of stack A.
 *
 * Rotates up (ra) if min_pos is in the first half, down (rra) otherwise.
 * Used to finish the sort with the smallest value on top.
 * essentially the rotate to top function rotate the stack A so that
 * the element at position min_pos (usuallly the min_value is moved to
 * the top of the stack)
 */
void	rotate_to_top(t_ps *data, int min_pos, int size_a)
{
	int	first_half;

	first_half = (min_pos <= size_a / 2);
	if (first_half)
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

/**
 * rotation_a - Rotates stack A a given number of times in a specified direction.
 * @data: Pointer to the main push_swap data structure.
 * @moves_a: Number of rotations to perform.
 * @rotate_a_up: If true, rotates up (ra); else, rotates down (rra).
 */
void	rotation_a(t_ps *data, int moves_a, bool rotate_a_up)
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

/**
 * rotation_b - Rotates stack B a given number of times in a specified direction.
 * @data: Pointer to the main push_swap data structure.
 * @moves_b: Number of rotations to perform.
 * @rotate_b_up: If true, rotates up (rb); else, rotates down (rrb).
 */
void	rotation_b(t_ps *data, int moves_b, bool rotate_b_up)
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

/**
 * final_rotation - Rotates stack A so the smallest value is on top.
 * @data: Pointer to the main push_swap data structure.
 *
 * Finds the minimum value in A, its position, and rotates A accordingly.
 * This is the final step to ensure the stack is fully sorted.
 * when we juse find_best_target it will finally return -1 
 * The number that return this value will be placed after the the first
 * position by default
 * so we need to put the in  order doing a last rotation
 *
 */
void	final_rotation(t_ps *data)
{
	int	min_value;
	int	min_pos;
	int	size_a;

	min_value = find_min_value_in_stack(&data->a);
	min_pos = 0;
	size_a = get_current_stack_size(&data->a);
	min_pos = find_min_pos(data, size_a, min_value);
	rotate_to_top(data, min_pos, size_a);
}
