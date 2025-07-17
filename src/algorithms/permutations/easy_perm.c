/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_perm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:14:38 by codespace         #+#    #+#             */
/*   Updated: 2025/07/17 09:54:35 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithms.h"
#include "push_swap.h"

static void	easy_sort_second(t_ps *data, t_chunk *to_sort);
static void	handle_top_b(t_ps *data, t_chunk *to_sort);
static void	handle_bottom_a(t_ps *data, t_chunk *to_sort);
static void	handle_bottom_b(t_ps *data, t_chunk *to_sort);

/**
 * easy_sort - Quickly sorts small chunks (usually 2 or 3 elements) in various stack locations.
 * @data: Pointer to the main push_swap data structure.
 * @to_sort: Pointer to the chunk to sort (location and size).
 *
 * This function is used for small, nearly sorted chunks. It checks if the top
 * element is the next in order, and if so, sorts it with sort_one or
 * easy_sort_second. This minimizes moves by handling sorted or nearly sorted
 * cases directly.
 *
 * Example:
 *   If the top of A is the next value needed, just move it to its place.
 *   If the next two are in order, use easy_sort_second for a 2-element swap.
 */
void	easy_sort(t_ps *data, t_chunk *to_sort)
{
	while (to_sort->loc != TOP_A && to_sort->size)
	{
		if (get_stack_element_at_position(&data->a, 1)
			== chunk_value(data, to_sort, 1) + 1 && to_sort->size > 0)
			sort_one(data, to_sort);
		else if (get_stack_element_at_position(&data->a, 1)
			== chunk_value(data, to_sort, 2) + 1 && to_sort->size > 1)
			easy_sort_second(data, to_sort);
		else
			break ;
	}
}

/**
 * easy_sort_second - Handles the case where the second element in the chunk is next in order.
 * @data: Pointer to the main push_swap data structure.
 * @to_sort: Pointer to the chunk to sort.
 *
 * Depending on the chunk's location, calls the appropriate handler to sort the
 * second element with minimal moves.
 */
static void	easy_sort_second(t_ps *data, t_chunk *to_sort)
{
	if (to_sort->loc == TOP_B)
		handle_top_b(data, to_sort);
	else if (to_sort->loc == BOTTOM_A)
		handle_bottom_a(data, to_sort);
	else if (to_sort->loc == BOTTOM_B)
		handle_bottom_b(data, to_sort);
	to_sort->size--;
}

/**
 * handle_top_b - Sorts two elements at the top of stack B and pushes them to A.
 * @data: Pointer to the main push_swap data structure.
 * @to_sort: Pointer to the chunk to sort.
 *
 * Swaps the top two of B if needed, then pushes to A. If the next element is
 * also in order, pushes it as well. This is optimal for small B chunks.
 */
static void	handle_top_b(t_ps *data, t_chunk *to_sort)
{
	sb(data);
	pa(data);
	if (get_stack_element_at_position(&data->b, 1)
		== get_stack_element_at_position(&data->a, 1) - 1)
	{
		pa(data);
		to_sort->size--;
	}
}

/**
 * handle_bottom_a - Sorts two elements at the bottom of stack A.
 * @data: Pointer to the main push_swap data structure.
 * @to_sort: Pointer to the chunk to sort.
 *
 * Rotates the bottom two to the top, swaps if needed, then rotates back.
 * This avoids unnecessary moves and keeps the chunk sorted in place.
 */
static void	handle_bottom_a(t_ps *data, t_chunk *to_sort)
{
	rra(data);
	rra(data);
	sa(data);
	if (get_stack_element_at_position(&data->a, 1)
		== get_stack_element_at_position(&data->a, 2) - 1)
		to_sort->size--;
	else
		ra(data);
}


/**
 * handle_bottom_b - Sorts two elements at the bottom of stack B and pushes to A.
 * @data: Pointer to the main push_swap data structure.
 * @to_sort: Pointer to the chunk to sort.
 *
 * Rotates the bottom two to the top of B, pushes to A, and if the next is in
 * order, pushes it as well. This is optimal for small B chunks at the bottom.
 */
static void	handle_bottom_b(t_ps *data, t_chunk *to_sort)
{
	rrb(data);
	rrb(data);
	pa(data);
	if (get_stack_element_at_position(&data->b, 1)
		== get_stack_element_at_position(&data->a, 1) - 1)
	{
		pa(data);
		to_sort->size--;
	}
	else
		rb(data);
}
