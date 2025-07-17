/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_perm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:32:28 by codespace         #+#    #+#             */
/*   Updated: 2025/07/17 09:54:42 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithms.h"
#include "push_swap.h"

/**
 * sort_one - Moves a single element from its current location to the top of A.
 * @data: Pointer to the main push_swap data structure.
 * @to_sort: Pointer to the chunk to sort.
 *
 * If the element is not already at the top of A, moves it there using
 * move_from_to. This is optimal for single elements, as it avoids unnecessary
 * operations and ensures the element is in place for further sorting.
 *
 * Example:
 *   If the element is at the bottom of B, moves it to the top of A in one step.
 */
void	sort_one(t_ps *data, t_chunk *to_sort)
{
	if (to_sort->loc == BOTTOM_A || to_sort->loc == BOTTOM_B
		|| to_sort->loc == TOP_B)
		move_from_to(data, to_sort->loc, TOP_A);
	to_sort->size -= 1;
}
