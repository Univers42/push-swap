/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_perm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 07:28:06 by codespace         #+#    #+#             */
/*   Updated: 2025/07/18 16:13:24 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	int	first;
	int	second;
	int	third;

	if (get_stack_size(&data->a) != 3)
		return ;
	first = get_items(&data->a, 1);
	second = get_items(&data->a, 2);
	third = get_items(&data->a, 3);
	if (first > second && second < third && first < third)
		sa(data);
	else if (first > second && second > third)
	{
		sa(data);
		rra(data);
	}
	else if (first > second && second < third && first > third)
		ra(data);
	else if (first < second && second > third && first < third)
	{
		sa(data);
		ra(data);
	}
	else if (first < second && second > third && first > third)
		rra(data);
}
