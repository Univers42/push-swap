/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_perm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 07:28:06 by codespace         #+#    #+#             */
/*   Updated: 2025/07/21 15:49:47 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "backtrack.h"
# include "algorithms.h"
/**
 * sort_three_simple - Sorts exactly three elements in stack A using minimal moves.
 * @data: Pointer to the main push_swap data structure.
 *
 * This function checks all possible orderings of three elements and applies the
 * minimal sequence of operations to sort them. It uses only sa, ra, and rra.
 *
 * Example:
 *   Stack: [3, 1, 2] (top to bottom)
 *   - first = 3, second = 1, third = 2
 *   - first > second && second < third && first > third: applies ra (rotate up)
 *   Result: [1, 2, 3]
 *
 * This approach is optimal because it covers all 6 permutations of 3 elements
 * and sorts them in at most 2 moves.
 * | #   | order | Operations |
| --- | ----- | ---------- |
| 1   | 1 2 3 | \0         |
| 2   | 1 3 2 | sa         |
| 3   | 2 1 3 | sa         |
| 4   | 2 3 1 | ra & sa    |
| 5   | 3 1 2 | ra         |
| 6   | 3 2 1 | rra        |
 */
void	sort_three_simple(t_ps *data)
{
	if (get_stack_size(&data->a) == 3 && get_stack_size(&data->b) == 0)
	{
		enhanced_sort_three_with_backtrack(data);
		return;
	}
}
