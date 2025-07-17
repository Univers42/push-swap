/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_perm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 22:31:18 by codespace         #+#    #+#             */
/*   Updated: 2025/07/17 09:56:36 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

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
	if (to_sort->loc == BOTTOM_A || to_sort->loc == BOTTOM_B
		|| to_sort->loc == TOP_B)
	{
		move_from_to(data, to_sort->loc, TOP_A);
		move_from_to(data, to_sort->loc, TOP_A);
	}
	if (get_stack_element_at_position(&data->a, 1)
		> get_stack_element_at_position(&data->a, 2))
		sa(data);
	to_sort->size -= 2;
}
