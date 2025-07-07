/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 01:17:48 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/07 02:10:25 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"
static void	sort_three_top_a(t_ps *data, t_chunk *to_sort, t_stack *stk,
				int max);
static void	sort_three_top_b(t_ps *data, t_chunk *to_sort, t_stack *stk,
				int max);
static void	sort_three_bottom_a(t_ps *data, t_chunk *to_sort, t_stack *stk,
				int max);
static void	sort_three_bottom_b(t_ps *data, t_chunk *to_sort, t_stack *stk,
				int max);

void	chunk_sort(t_ps *data)
{
	t_chunk	chunk_all;

	chunk_all.loc = TOP_A;
	chunk_all.size = data->a.capacity;
	rec_chunk_sort(data, &chunk_all);
}

void	rec_chunk_sort(t_ps *data, t_chunk *to_sort)
{
	t_split_dest	dest;

	chunk_to_the_top(data, to_sort);
	easy_sort(data, to_sort);
	if (to_sort->size <= 3)
	{
		if (to_sort->size == 3)
			sort_three(data, to_sort);
		else if (to_sort->size == 2)
			sort_two(data, to_sort);
		else if (to_sort->size == 1)
			sort_one(data, to_sort);
		return ;
	}
	chunk_split(data, to_sort, &dest);
	rec_chunk_sort(data, &dest.max);
	rec_chunk_sort(data, &dest.mid);
	rec_chunk_sort(data, &dest.min);
}

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

void	sort_one(t_ps *data, t_chunk *to_sort)
{
	if (to_sort->loc == BOTTOM_A || to_sort->loc == BOTTOM_B
		|| to_sort->loc == TOP_B)
		move_from_to(data, to_sort->loc, TOP_A);
	to_sort->size -= 1;
}

static void	innit_size(t_chunk *min, t_chunk *mid, t_chunk *max);
static void	set_split_loc(t_loc loc, t_chunk *min, t_chunk *mid, t_chunk *max);
static void	set_third_pivots(t_loc loc, int crt_size, int *pivot_1,
				int *pivot_2);

void	chunk_split(t_ps *data, t_chunk *to_split, t_split_dest *dest)
{
	int	pivot_1;
	int	pivot_2;
	int	max_value;
	int	next_value;

	innit_size(&dest->min, &dest->mid, &dest->max);
	set_split_loc(to_split->loc, &dest->min, &dest->mid, &dest->max);
	set_third_pivots(to_split->loc, to_split->size, &pivot_1, &pivot_2);
	max_value = chunk_max_value(data, to_split);
	while (to_split->size--)
	{
		next_value = chunk_value(data, to_split, 1);
		if (next_value > max_value - pivot_2)
		{
			dest->max.size += move_from_to(data, to_split->loc, dest->max.loc);
			split_max_reduction(data, &dest->max);
			if (a_partly_sort(data, 1) && to_split->size)
				easy_sort(data, to_split);
		}
		else if (next_value > max_value - pivot_1)
			dest->mid.size += move_from_to(data, to_split->loc, dest->mid.loc);
		else
			dest->min.size += move_from_to(data, to_split->loc, dest->min.loc);
	}
}

static void	innit_size(t_chunk *min, t_chunk *mid, t_chunk *max)
{
	min->size = 0;
	mid->size = 0;
	max->size = 0;
}

static void	set_split_loc(t_loc loc, t_chunk *min, t_chunk *mid, t_chunk *max)
{
	if (loc == TOP_A)
	{
		min->loc = BOTTOM_B;
		mid->loc = TOP_B;
		max->loc = BOTTOM_A;
	}
	else if (loc == BOTTOM_A)
	{
		min->loc = BOTTOM_B;
		mid->loc = TOP_B;
		max->loc = TOP_A;
	}
	else if (loc == TOP_B)
	{
		min->loc = BOTTOM_B;
		mid->loc = BOTTOM_A;
		max->loc = TOP_A;
	}
	else if (loc == BOTTOM_B)
	{
		min->loc = TOP_B;
		mid->loc = BOTTOM_A;
		max->loc = TOP_A;
	}
}

static void	set_third_pivots(t_loc loc, int crt_size, int *pivot_1,
				int *pivot_2)
{
	*pivot_2 = crt_size / 3;
	*pivot_1 = 2 * crt_size / 3;
	if (loc == TOP_B || loc == BOTTOM_B)
		*pivot_1 = crt_size / 2;
	if ((loc == TOP_A || loc == BOTTOM_A) && crt_size < 15)
		*pivot_1 = crt_size;
	if (loc == BOTTOM_B && crt_size < 8)
		*pivot_2 = crt_size / 2;
}

void	chunk_to_the_top(t_ps *data, t_chunk *to_sort)
{
	if (to_sort->loc == BOTTOM_B
		&& get_current_stack_size(&data->b) == to_sort->size)
		to_sort->loc = TOP_B;
	if (to_sort->loc == BOTTOM_A
		&& get_current_stack_size(&data->a) == to_sort->size)
		to_sort->loc = TOP_A;
}

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

void	split_max_reduction(t_ps *data, t_chunk *max)
{
	t_stack	*a;

	a = &data->a;
	if (max->loc == TOP_A && max->size == 3
		&& is_consecutive(get_stack_element_at_position(a, 1),
			get_stack_element_at_position(a, 2),
			get_stack_element_at_position(a, 3),
			get_stack_element_at_position(a, 4))
		&& a_partly_sort(data, 4))
	{
		sort_three(data, max);
		return ;
	}
	if (max->loc == TOP_A
		&& get_stack_element_at_position(a, 1)
		== get_stack_element_at_position(a, 3) - 1
		&& a_partly_sort(data, 3))
	{
		sa(data);
		max->size--;
	}
	if (max->loc == TOP_A && a_partly_sort(data, 1))
		max->size--;
}

bool	a_partly_sort(t_ps *data, int from)
{
	int		i;
	t_stack	*a;
	int		value_current;

	a = &data->a;
	i = a->top;
	while (--from)
		i = calculate_next_down_index(a, i);
	while (a->stack[i] != data->a.capacity)
	{
		value_current = a->stack[i];
		i = calculate_next_down_index(a, i);
		if (a->stack[i] != value_current + 1)
			return (false);
	}
	return (true);
}

bool	is_consecutive(int a, int b, int c, int d)
{
	ft_swap(&a, &b, sizeof(int));
	ft_swap(&b, &c, sizeof(int));
	return ((b - a == 1) && (c - b == 1) && (d - c == 1));
}

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

int	get_stack_element_at_position(t_stack *stk, int position)
{
	int	target_index;

	if (position <= 0 || stk->element_count == 0)
		return (0);
	if (position == 1)
		return (stk->stack[stk->top]);
	target_index = (stk->top + (position - 1)) % stk->capacity;
	return (stk->stack[target_index]);
}

int	get_current_stack_size(t_stack *stk)
{
	if (!stk)
		return (0);
	return (stk->element_count);
}

int	calculate_next_up_index(t_stack *stk, int index)
{
	if (index == 0)
		return (stk->capacity - 1);
	return (index - 1);
}

int	calculate_next_down_index(t_stack *stk, int index)
{
	if (index == stk->capacity - 1)
		return (0);
	return (index + 1);
}