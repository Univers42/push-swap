/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_perm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:11:23 by codespace         #+#    #+#             */
/*   Updated: 2025/07/21 15:43:52 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"
#include "backtrack.h"

static void	sort_three_top_a(t_ps *data, t_chunk *to_sort, t_stack *stk,
				int max);
static void	sort_three_top_b(t_ps *data, t_chunk *to_sort, t_stack *stk,
				int max);
static void	sort_three_bottom_a(t_ps *data, t_chunk *to_sort, t_stack *stk,
				int max);
static void	sort_three_bottom_b(t_ps *data, t_chunk *to_sort, t_stack *stk,
				int max);

/**
 * sort_three - Sorts three elements in a chunk, regardless of their location and stack.
 * @data: Pointer to the main push_swap data structure.
 * @to_sort: Pointer to the chunk to sort.
 *
 * Determines the chunk's location (top/bottom of A/B) and calls the appropriate
 * helper to sort the three elements with minimal moves. This is optimal because
 * it uses the minimum number of stack operations for each case.
 *
 * Example:
 *   If the chunk is at the top of B, uses pa and sb to bring the largest to A
 *   and sort the rest.
 */
void	sort_three(t_ps *data, t_chunk *to_sort)
{
	// Use backtracking for three elements if stack is very small
	if (get_stack_size(&data->a) + get_stack_size(&data->b) <= 6)
	{
		if (backtrack_sort(data, 3))
		{
			to_sort->size -= 3;
			return;
		}
	}
	t_stack	*stk;
	int		max;

	stk = loc_to_stack(data, to_sort->loc);
	max = chunk_max_value(data, to_sort);
	if (to_sort->loc == TOP_A)
		sort_three_top_a(data, to_sort, stk, max);
	else if (to_sort->loc == BOTTOM_A)
		sort_three_bottom_a(data, to_sort, stk, max);
	else if (to_sort->loc == TOP_B)
		sort_three_top_b(data, to_sort, stk, max);
	else if (to_sort->loc == BOTTOM_B)
		sort_three_bottom_b(data, to_sort, stk, max);
}

/**
 * sort_three_top_a - Sorts three elements at the top of stack A.
 * @data: Pointer to the main push_swap data structure.
 * @to_sort: Pointer to the chunk to sort.
 * @stk: Pointer to the stack structure.
 * @max: Maximum value in the chunk.
 *
 * Uses a combination of sa, ra, and rra to sort the three elements in place.
 * This is optimal for the top of A, as it avoids unnecessary pushes.
 */
static void	sort_three_top_a(t_ps *data, t_chunk *to_sort, t_stack *stk,
		int max)
{
	if (stk->stack[stk->top] == max)
	{
		sa(data);
		ra(data);
		sa(data);
		rra(data);
	}
	else if (stk->stack[move_down(stk, stk->top)] == max)
	{
		ra(data);
		sa(data);
		rra(data);
	}
	to_sort->loc = TOP_A;
	to_sort->size -= 1;
	sort_two(data, to_sort);
}

/**
 * sort_three_top_b - Sorts three elements at the top of stack B and pushes to A.
 * @data: Pointer to the main push_swap data structure.
 * @to_sort: Pointer to the chunk to sort.
 * @stk: Pointer to the stack structure.
 * @max: Maximum value in the chunk.
 *
 * Uses pa and sb to bring the largest to A and sort the rest, then pushes all
 * to A. This is optimal for B, as it minimizes the number of operations.
 */
static void	sort_three_top_b(t_ps *data, t_chunk *to_sort, t_stack *stk,
		int max)
{
	pa(data);
	if (stk->stack[stk->top] == max)
	{
		pa(data);
		sa(data);
	}
	else if (stk->stack[move_down(stk, stk->top)] == max)
	{
		sb(data);
		pa(data);
		sa(data);
	}
	else
		pa(data);
	pa(data);
	to_sort->loc = TOP_A;
	to_sort->size -= 1;
	sort_two(data, to_sort);
}

/**
 * sort_three_bottom_a - Sorts three elements at the bottom of stack A.
 * @data: Pointer to the main push_swap data structure.
 * @to_sort: Pointer to the chunk to sort.
 * @stk: Pointer to the stack structure.
 * @max: Maximum value in the chunk.
 *
 * Rotates the bottom three to the top, sorts them, then rotates back if needed.
 * This is optimal for bottom chunks, as it avoids unnecessary pushes.
 */
static void	sort_three_bottom_a(t_ps *data, t_chunk *to_sort, t_stack *stk,
		int max)
{
	rra(data);
	rra(data);
	if (stk->stack[stk->top] == max)
	{
		sa(data);
		rra(data);
	}
	else if (stk->stack[move_down(stk, stk->top)] == max)
		rra(data);
	else
	{
		pb(data);
		rra(data);
		sa(data);
		pa(data);
	}
	to_sort->loc = TOP_A;
	to_sort->size -= 1;
	sort_two(data, to_sort);
}

/**
 * sort_three_bottom_b - Sorts three elements at the bottom of stack B and pushes to A.
 * @data: Pointer to the main push_swap data structure.
 * @to_sort: Pointer to the chunk to sort.
 * @stk: Pointer to the stack structure.
 * @max: Maximum value in the chunk.
 *
 * Rotates the bottom three to the top of B, sorts them, then pushes to A.
 * This is optimal for bottom B, as it minimizes the number of moves.
 */
static void	sort_three_bottom_b(t_ps *data, t_chunk *to_sort, t_stack *stk,
		int max)
{
	rrb(data);
	rrb(data);
	if (stk->stack[stk->top] == max)
	{
		pa(data);
		rrb(data);
	}
	else if (stk->stack[move_down(stk, stk->top)] == max)
	{
		sb(data);
		pa(data);
		rrb(data);
	}
	else
	{
		rrb(data);
		pa(data);
	}
	to_sort->loc = TOP_B;
	to_sort->size -= 1;
	sort_two(data, to_sort);
}
