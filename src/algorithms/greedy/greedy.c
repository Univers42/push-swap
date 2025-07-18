/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:52:32 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/18 16:26:00 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

/**
 * greedy_sort - Main entry point for the greedy sorting algorithm.
 * @data: Pointer to the main push_swap data structure.
 *
 * This function orchestrates the greedy sort:
 *   - Handles trivial cases (2 or 3 elements).
 *   - Checks if already sorted.
 *   - Pushes elements to stack B using push_to_b().
 *   - Pushes them back to A in optimal order using push_back_to_a().
 *   - Rotates A so the smallest element is on top (final_rotation()).
 *@note: There are broady to phase, one of them is to 
 * Example:
 *   For a stack of 5+ elements, this function will split, sort, and merge using the greedy strategy.
 */
void	greedy_sort(t_ps *data)
{
	if (!data || data->total_size <= 3)
	{
		if (data->total_size == 3)
			sort_three_simple(data);
		else if (data->total_size == 2
			&& get_items(&data->a, 1)
			> get_items(&data->a, 2))
			sa(data);
		return ;
	}
	if (is_stack_sorted(data))
		return ;
	data->algo_ctx.u_ctx.s_greedy.phase = 0;
	push_to_b(data);
	data->algo_ctx.u_ctx.s_greedy.phase = 1;
	push_back_to_a(data);
	final_rotation(data);
}
