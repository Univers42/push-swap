/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_perm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 22:31:18 by codespace         #+#    #+#             */
/*   Updated: 2025/07/21 15:49:13 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"
#include "backtrack.h"

/**
 * sort_two - Sorts two elements in a chunk, regardless of their location.
 * @data: Pointer to the main push_swap data structure.
 * @to_sort: Pointer to the chunk to sort.
 *
 * If the two elements are not at the top of A, moves them there. Then, if
 * needed, swaps them to ensure ascending order. This is optimal for two
 * elements, as it uses at most two moves to bring them to the top and one swap.
 *
 * Example:
 *   If the two elements are [2, 1] at the top of A, applies sa to get [1, 2].
 */
void	sort_two(t_ps *data, t_chunk *to_sort)
{
	// Use backtracking for two elements if stack is very small
	if (get_stack_size(&data->a) + get_stack_size(&data->b) <= 6)
	{
		if (backtrack_sort(data, 2))
		{
			to_sort->size -= 2;
			return;
		}
	}
	if (to_sort->loc == BOTTOM_A || to_sort->loc == BOTTOM_B
		|| to_sort->loc == TOP_B)
	{
		transfer_chunk(data, to_sort->loc, TOP_A);
		transfer_chunk(data, to_sort->loc, TOP_A);
	}
	if (get_items(&data->a, 1)
		> get_items(&data->a, 2))
		sa(data);
	to_sort->size -= 2;
}
