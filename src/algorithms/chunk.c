/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 01:17:48 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/07 12:33:37 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"
#include <limits.h>

/* Forward declarations */
static void move_from_top_a(t_ps *data, t_loc to);
static void move_from_top_b(t_ps *data, t_loc to);
static void move_from_bottom_a(t_ps *data, t_loc to);
static void move_from_bottom_b(t_ps *data, t_loc to);
static void innit_size(t_chunk *min, t_chunk *mid, t_chunk *max);
static void rec_chunk_sort(t_ps *data, t_chunk *to_sort);
static void sort_two_chunk(t_ps *data, t_chunk *to_sort);
static void sort_three_chunk(t_ps *data, t_chunk *to_sort);
static void easy_sort_second(t_ps *data, t_chunk *to_sort);
static void handle_top_b(t_ps *data, t_chunk *to_sort);
static void handle_bottom_a(t_ps *data, t_chunk *to_sort);
static void handle_bottom_b(t_ps *data, t_chunk *to_sort);

/* Additional forward declarations for functions used before definition */
void split_max_reduction(t_ps *data, t_chunk *max);
void easy_sort(t_ps *data, t_chunk *to_sort);
void sort_three_complex(t_ps *data, t_chunk *to_sort);

/* Helper Functions */
t_stack	*loc_to_stack(t_ps *data, t_loc loc)
{
	if (loc == TOP_A || loc == BOTTOM_A)
		return (&data->stack_a);
	else
		return (&data->stack_b);
}

int	chunk_max_value(t_ps *data, t_chunk *chunk)
{
	t_stack	*stk;
	int		max_value;
	int		i;
	int		start_idx;
	int		count;

	stk = loc_to_stack(data, chunk->loc);
	max_value = INT_MIN;
	
	// Determine starting index based on location
	if (chunk->loc == TOP_A || chunk->loc == TOP_B)
		start_idx = 0;  // Top starts from index 0
	else
		start_idx = stk->element_count - chunk->size;  // Bottom starts from end
	
	// Check bounds
	if (start_idx < 0)
		start_idx = 0;
	
	// Iterate through the chunk elements
	count = 0;
	for (i = start_idx; i < stk->element_count && count < chunk->size; i++, count++)
	{
		if (stk->stack[i] > max_value)
			max_value = stk->stack[i];
	}
	return (max_value);
}

int	chunk_value(t_ps *data, t_chunk *chunk, int n)
{
	t_stack	*stk;
	int		idx;

	stk = loc_to_stack(data, chunk->loc);
	if (n <= 0 || n > chunk->size || n > stk->element_count)
		return (0);
	
	// Calculate actual index based on location and position
	if (chunk->loc == TOP_A || chunk->loc == TOP_B)
		idx = n - 1;  // Top: n=1 means index 0
	else
		idx = stk->element_count - chunk->size + (n - 1);  // Bottom: count from end
	
	// Bounds check
	if (idx < 0 || idx >= stk->element_count)
		return (0);
		
	return (stk->stack[idx]);
}

/* Movement operations */
int	move_from_to(t_ps *data, t_loc from, t_loc to)
{
	if (from == TOP_A)
		move_from_top_a(data, to);
	else if (from == TOP_B)
		move_from_top_b(data, to);
	else if (from == BOTTOM_A)
		move_from_bottom_a(data, to);
	else if (from == BOTTOM_B)
		move_from_bottom_b(data, to);
	return (1);
}

static void	move_from_top_a(t_ps *data, t_loc to)
{
	if (to == TOP_B)
		pb(data);
	else if (to == BOTTOM_A)
		ra(data);
	else if (to == BOTTOM_B)
	{
		pb(data);
		rb(data);
	}
}

static void	move_from_top_b(t_ps *data, t_loc to)
{
	if (to == TOP_A)
		pa(data);
	else if (to == BOTTOM_B)
		rb(data);
	else if (to == BOTTOM_A)
	{
		pa(data);
		ra(data);
	}
}

static void	move_from_bottom_a(t_ps *data, t_loc to)
{
	if (to == TOP_A)
		rra(data);
	else if (to == TOP_B)
	{
		rra(data);
		pb(data);
	}
	else if (to == BOTTOM_B)
	{
		rra(data);
		pb(data);
		rb(data);
	}
}

static void	move_from_bottom_b(t_ps *data, t_loc to)
{
	if (to == TOP_B)
		rrb(data);
	else if (to == TOP_A)
	{
		rrb(data);
		pa(data);
	}
	else if (to == BOTTOM_A)
	{
		rrb(data);
		pa(data);
		ra(data);
	}
}

/* Sorting utilities */
bool	a_partly_sort(t_ps *data, int from)
{
	int i;

	if (!data || from <= 0 || from > data->stack_a.element_count)
		return (false);

	// Check if elements from 'from' position onwards are sorted
	// Convert from 1-based to 0-based index
	for (i = from - 1; i < data->stack_a.element_count - 1; i++)
	{
		if (data->stack_a.stack[i] > data->stack_a.stack[i + 1])
			return (false);
	}
	return (true);
}

void	chunk_to_the_top(t_ps *data, t_chunk *to_sort)
{
	if (to_sort->loc == BOTTOM_B
		&& get_current_stack_size(&data->stack_b) == to_sort->size)
		to_sort->loc = TOP_B;
	if (to_sort->loc == BOTTOM_A
		&& get_current_stack_size(&data->stack_a) == to_sort->size)
		to_sort->loc = TOP_A;
}

/* Split operations */
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

/* Sort functions */
static void sort_one(t_ps *data, t_chunk *to_sort)
{
	if (!data || !to_sort || to_sort->size <= 0)
		return;

	// Only move if not already at TOP_A
	if (to_sort->loc != TOP_A)
		move_from_to(data, to_sort->loc, TOP_A);
	
	to_sort->size = 0;
	to_sort->loc = TOP_A;
}

static void sort_three_chunk(t_ps *data, t_chunk *to_sort)
{
	if (!data || !to_sort || to_sort->size < 3)
		return;

	// Call the complex version which handles all locations
	sort_three_complex(data, to_sort);
}

void	chunk_split(t_ps *data, t_chunk *to_split, t_split_dest *dest)
{
	int	pivot_1;
	int	pivot_2;
	int	max_value;
	int	next_value;
	int original_size;

	innit_size(&dest->min, &dest->mid, &dest->max);
	set_split_loc(to_split->loc, &dest->min, &dest->mid, &dest->max);
	set_third_pivots(to_split->loc, to_split->size, &pivot_1, &pivot_2);
	max_value = chunk_max_value(data, to_split);
	
	ft_printf("DEBUG: chunk_split - size=%d, max_value=%d, pivot1=%d, pivot2=%d\n",
		to_split->size, max_value, pivot_1, pivot_2);
	
	original_size = to_split->size;
	while (to_split->size > 0)
	{
		next_value = chunk_value(data, to_split, 1);
		
		ft_printf("DEBUG: Processing value %d (size remaining: %d)\n", 
			next_value, to_split->size);
		
		if (next_value > max_value - pivot_2)
		{
			dest->max.size += move_from_to(data, to_split->loc, dest->max.loc);
			to_split->size--;  // Decrement here
			split_max_reduction(data, &dest->max);
			if (a_partly_sort(data, 1) && to_split->size > 0)
				easy_sort(data, to_split);
		}
		else if (next_value > max_value - pivot_1)
		{
			dest->mid.size += move_from_to(data, to_split->loc, dest->mid.loc);
			to_split->size--;  // Decrement here
		}
		else
		{
			dest->min.size += move_from_to(data, to_split->loc, dest->min.loc);
			to_split->size--;  // Decrement here
		}
		
		// Safety check
		if (dest->max.size + dest->mid.size + dest->min.size > original_size)
		{
			ft_printf("ERROR: Split produced more elements than original!\n");
			break;
		}
	}
}

static void	innit_size(t_chunk *min, t_chunk *mid, t_chunk *max)
{
	min->size = 0;
	mid->size = 0;
	max->size = 0;
}

/* Main recursive chunk sort */
static void rec_chunk_sort(t_ps *data, t_chunk *to_sort)
{
	t_split_dest dest;
	static int depth = 0;  // Add recursion depth tracking
	
	if (!data || !to_sort || to_sort->size <= 0)
		return;
		
	// Prevent infinite recursion
	depth++;
	if (depth > 100)
	{
		ft_printf("ERROR: Maximum recursion depth reached!\n");
		depth--;
		return;
	}
	
	ft_printf("DEBUG: rec_chunk_sort - depth=%d, size=%d, loc=%d\n", 
		depth, to_sort->size, to_sort->loc);
	
	chunk_to_the_top(data, to_sort);
	
	// Handle small chunks directly
	if (to_sort->size == 1)
	{
		sort_one(data, to_sort);
		depth--;
		return;
	}
	else if (to_sort->size == 2)
	{
		sort_two_chunk(data, to_sort);
		depth--;
		return;
	}
	else if (to_sort->size == 3)
	{
		sort_three_chunk(data, to_sort);
		depth--;
		return;
	}
	
	// Split larger chunks
	chunk_split(data, to_sort, &dest);
	
	ft_printf("DEBUG: After split - max:%d, mid:%d, min:%d\n",
		dest.max.size, dest.mid.size, dest.min.size);
	
	// Recursively sort sub-chunks (order matters!)
	if (dest.max.size > 0)
		rec_chunk_sort(data, &dest.max);
	if (dest.mid.size > 0)
		rec_chunk_sort(data, &dest.mid);
	if (dest.min.size > 0)
		rec_chunk_sort(data, &dest.min);
		
	depth--;
}

/* Main entry point */
void chunk_sort(t_ps *data)
{
	t_chunk chunk_all;

	if (!data)
		return;
	
	chunk_all.loc = TOP_A;
	chunk_all.size = data->stack_a.element_count;
	
	if (chunk_all.size <= 1)
		return;
	
	rec_chunk_sort(data, &chunk_all);
}

/* Additional helper functions */
void	easy_sort(t_ps *data, t_chunk *to_sort)
{
	while (to_sort->loc != TOP_A && to_sort->size)
	{
		if (get_stack_element_at_position(&data->stack_a, 1)
			== chunk_value(data, to_sort, 1) + 1 && to_sort->size > 0)
			sort_one(data, to_sort);
		else if (get_stack_element_at_position(&data->stack_a, 1)
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
	if (get_stack_element_at_position(&data->stack_b, 1)
		== get_stack_element_at_position(&data->stack_a, 1) - 1)
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
	if (get_stack_element_at_position(&data->stack_a, 1)
		== get_stack_element_at_position(&data->stack_a, 2) - 1)
		to_sort->size--;
	else
		ra(data);
}

static void	handle_bottom_b(t_ps *data, t_chunk *to_sort)
{
	rrb(data);
	rrb(data);
	pa(data);
	if (get_stack_element_at_position(&data->stack_b, 1)
		== get_stack_element_at_position(&data->stack_a, 1) - 1)
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

	a = &data->stack_a;
	if (max->loc == TOP_A && max->size == 3
		&& is_consecutive(get_stack_element_at_position(a, 1),
			get_stack_element_at_position(a, 2),
			get_stack_element_at_position(a, 3),
			get_stack_element_at_position(a, 4))
		&& a_partly_sort(data, 4))
	{
		sort_three_chunk(data, max);
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

bool	is_consecutive(int a, int b, int c, int d)
{
	// Check if the values are consecutive (don't swap them!)
	return ((b - a == 1) && (c - b == 1) && (d - c == 1));
}


void	sort_three_complex(t_ps *data, t_chunk *to_sort)
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

static void	sort_two_chunk (t_ps *data, t_chunk *to_sort)
{
	int val1, val2;
	
	if (!data || !to_sort || to_sort->size < 2)
		return;
		
	// Move both elements to TOP_A if needed
	if (to_sort->loc != TOP_A)
	{
		move_from_to(data, to_sort->loc, TOP_A);
		if (to_sort->size > 1)
			move_from_to(data, to_sort->loc, TOP_A);
	}
	
	// Check if we need to swap
	if (data->stack_a.element_count >= 2)
	{
		val1 = data->stack_a.stack[0];
		val2 = data->stack_a.stack[1];
		if (val1 > val2)
			sa(data);
	}
	
	to_sort->size = 0;
	to_sort->loc = TOP_A;
}

void	sort_three_top_a(t_ps *data, t_chunk *to_sort, t_stack *stk,
		int max)
{
	// For array-based stack, top elements are at indices 0, 1, 2
	if (stk->element_count < 3)
		return;
		
	if (stk->stack[0] == max)
	{
		sa(data);
		ra(data);
		sa(data);
		rra(data);
	}
	else if (stk->stack[1] == max)
	{
		ra(data);
		sa(data);
		rra(data);
	}
	// If max is at position 2, it's already in the right place for this chunk
	
	to_sort->loc = TOP_A;
	to_sort->size = 2;  // Reduce to handle remaining 2 elements
	sort_two_chunk(data, to_sort);
}

void	sort_three_top_b(t_ps *data, t_chunk *to_sort, t_stack *stk,
		int max)
{
	// Move all to stack A first
	pa(data);
	
	if (stk->element_count >= 2 && stk->stack[0] == max)
	{
		pa(data);
		if (stk->element_count >= 1)
			pa(data);
		// Now we have 3 elements at top of A, max is second
		sa(data);  // Put max at top
		ra(data);  // Move max down
		sa(data);  // Sort remaining two if needed
		rra(data); // Bring max back
	}
	else if (stk->element_count >= 2 && stk->stack[1] == max)
	{
		sb(data);  // Put max at top of B
		pa(data);  // Move max to A
		if (stk->element_count >= 1)
			pa(data);  // Move last element
	}
	else
	{
		// Max is at position 2 (bottom of the 3)
		if (stk->element_count >= 1)
			pa(data);
		if (stk->element_count >= 1)
			pa(data);
	}
	
	// Now sort the 3 elements at top of A
	to_sort->loc = TOP_A;
	to_sort->size = 3;
	
	// Simple 3-element sort on top of A
	if (data->stack_a.element_count >= 3)
	{
		int a = data->stack_a.stack[0];
		int b = data->stack_a.stack[1];
		int c = data->stack_a.stack[2];
		
		if (a > b && b < c && a < c)
			sa(data);
		else if (a > b && b > c)
		{
			sa(data);
			ra(data);
			ra(data);
			ra(data);
			rra(data);
			rra(data);
			rra(data);
			sa(data);
		}
		// Add other cases as needed
	}
	
	to_sort->size = 0;
}

void	sort_three_bottom_a(t_ps *data, t_chunk *to_sort, t_stack *stk,
		int max)
{
	int bottom_idx;
	
	// For array-based stack, bottom elements are at the end
	bottom_idx = stk->element_count - 3;  // Start of the 3-element chunk
	
	if (bottom_idx < 0)
		return;
	
	// Bring bottom 3 elements to top
	rra(data);
	rra(data);
	rra(data);
	
	// Now they're at top, check which one is max
	if (stk->stack[0] == max)
	{
		ra(data);
		sa(data);
		ra(data);
		ra(data);
	}
	else if (stk->stack[1] == max)
	{
		sa(data);
		ra(data);
		ra(data);
		ra(data);
	}
	else  // max is at position 2
	{
		// Max is already in correct position relative to the chunk
		ra(data);
		ra(data);
		ra(data);
	}
	
	to_sort->size = 0;
	to_sort->loc = TOP_A;
}

void	sort_three_bottom_b(t_ps *data, t_chunk *to_sort, t_stack *stk,
		int max)
{
    (void)max;
	int bottom_idx;
	
	// For array-based stack, bottom elements are at the end
	bottom_idx = stk->element_count - 3;  // Start of the 3-element chunk
	
	if (bottom_idx < 0)
		return;
		
	// Bring bottom 3 elements to top
	rrb(data);
	rrb(data);
	rrb(data);
	
	// Move all to stack A
	pa(data);
	pa(data);
	pa(data);
	
	// Now sort the 3 elements at top of A
	if (data->stack_a.element_count >= 3)
	{
		int a = data->stack_a.stack[0];
		int b = data->stack_a.stack[1];
		int c = data->stack_a.stack[2];
		
		if (a > b && b < c && a < c)
			sa(data);
		else if (a > b && b > c)
		{
			sa(data);
			rra(data);
		}
		else if (a > b && b < c && a > c)
			ra(data);
		else if (a < b && b > c && a < c)
		{
			sa(data);
			ra(data);
		}
		else if (a < b && b > c && a > c)
			rra(data);
	}
	
	to_sort->size = 0;
	to_sort->loc = TOP_A;
}

/* Compatibility functions for array-based stack */
int	get_stack_element_at_position(t_stack *stk, int position)
{
	if (!stk || position <= 0 || position > stk->element_count)
		return (0);
	return (stk->stack[position - 1]);
}

int	get_current_stack_size(t_stack *stk)
{
	if (!stk)
		return (0);
	return (stk->element_count);
}

int	calculate_next_up_index(t_stack *stk, int index)
{
	// For array-based stack, moving up means decreasing index
	if (index <= 0)
		return (stk->element_count - 1);
	return (index - 1);
}

int	calculate_next_down_index(t_stack *stk, int index)
{
	// For array-based stack, moving down means increasing index
	if (index >= stk->element_count - 1)
		return (0);
	return (index + 1);
}