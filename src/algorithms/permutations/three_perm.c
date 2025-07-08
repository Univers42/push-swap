/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_perm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:11:23 by codespace         #+#    #+#             */
/*   Updated: 2025/07/08 14:12:47 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

static void	sort_three_top_a(t_ps *data, t_chunk *to_sort, t_stack *stk,
				int max);
static void	sort_three_top_b(t_ps *data, t_chunk *to_sort, t_stack *stk,
				int max);
static void	sort_three_bottom_a(t_ps *data, t_chunk *to_sort, t_stack *stk,
				int max);
static void	sort_three_bottom_b(t_ps *data, t_chunk *to_sort, t_stack *stk,
				int max);

void	sort_three(t_ps *data, t_chunk *to_sort)
{
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
	else if (stk->stack[calculate_next_down_index(stk, stk->top)] == max)
	{
		ra(data);
		sa(data);
		rra(data);
	}
	to_sort->loc = TOP_A;
	to_sort->size -= 1;
	sort_two(data, to_sort);
}

static void	sort_three_top_b(t_ps *data, t_chunk *to_sort, t_stack *stk,
		int max)
{
	pa(data);
	if (stk->stack[stk->top] == max)
	{
		pa(data);
		sa(data);
	}
	else if (stk->stack[calculate_next_down_index(stk, stk->top)] == max)
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
	else if (stk->stack[calculate_next_down_index(stk, stk->top)] == max)
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
	else if (stk->stack[calculate_next_down_index(stk, stk->top)] == max)
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
