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

// Forward declarations
static void sort_three_top_a(t_ps *data, t_chunk *to_sort, int max);
static void sort_three_top_b(t_ps *data, t_chunk *to_sort, int max);
static void sort_three_bottom_a(t_ps *data, t_chunk *to_sort, int max);
static void sort_three_bottom_b(t_ps *data, t_chunk *to_sort, int max);
static void init_size(t_chunk *min, t_chunk *mid, t_chunk *max);
static void set_split_loc(t_loc loc, t_chunk *min, t_chunk *mid, t_chunk *max);
static void set_third_pivots(t_loc loc, int crt_size, int *pivot_1, int *pivot_2);
static void easy_sort_second(t_ps *data, t_chunk *to_sort);
static void handle_top_b(t_ps *data, t_chunk *to_sort);
static void handle_bottom_a(t_ps *data, t_chunk *to_sort);
static void handle_bottom_b(t_ps *data, t_chunk *to_sort);
static int 	chunk_max_value(t_ps *data, t_chunk *chunk);
static int 	chunk_value(t_ps *data, t_chunk *chunk, int position);
static int 	move_from_to(t_ps *data, t_loc from, t_loc to);
static void chunk_to_the_top(t_ps *data, t_chunk *to_sort);
static void easy_sort(t_ps *data, t_chunk *to_sort);
static void split_max_reduction(t_ps *data, t_chunk *max);
static bool a_partly_sort(t_ps *data, int from);
static bool is_consecutive(int a, int b, int c, int d);
static void rec_chunk_sort(t_ps *data, t_chunk *to_sort);
static void sort_one(t_ps *data, t_chunk *to_sort);
static void sort_two_chunk(t_ps *data, t_chunk *to_sort);
static void sort_three_chunk(t_ps *data, t_chunk *to_sort);
static void chunk_split(t_ps *data, t_chunk *to_split, t_split_dest *dest);
static int	calculate_next_down_index(t_stack *stk, int index);
static int	calculate_next_up_index(t_stack *stk, int index);
static void update_sizes(t_ps *data);
static t_stack	*loc_to_stack(t_ps *data, t_loc loc);
// Main chunk sort function
void chunk_sort(t_ps *data)
{
    t_chunk chunk_all;

    if (!data || !data->stack_a)
        return;
    
    // Update sizes first
    update_sizes(data);
    
    chunk_all.loc = TOP_A;
    chunk_all.size = data->size_a;
    
    if (chunk_all.size <= 1)
        return;
    
    rec_chunk_sort(data, &chunk_all);
    
    // Final size update
    update_sizes(data);
}

static void rec_chunk_sort(t_ps *data, t_chunk *to_sort)
{
    t_split_dest dest;

    if (!data || !to_sort || to_sort->size <= 0)
        return;
    
    chunk_to_the_top(data, to_sort);
    easy_sort(data, to_sort);
    
    if (to_sort->size <= 3)
    {
        if (to_sort->size == 3)
            sort_three_chunk(data, to_sort);
        else if (to_sort->size == 2)
            sort_two_chunk(data, to_sort);
        else if (to_sort->size == 1)
            sort_one(data, to_sort);
        return;
    }
    
    chunk_split(data, to_sort, &dest);
    
    if (dest.max.size > 0)
        rec_chunk_sort(data, &dest.max);
    if (dest.mid.size > 0)
        rec_chunk_sort(data, &dest.mid);
    if (dest.min.size > 0)
        rec_chunk_sort(data, &dest.min);
}

// Safe helper functions to work with t_list
static int get_list_element_at_position(t_stack *list, int position)
{
    if (!list || position <= 0)
        return (0);
    
    t_stack *current = list;
    int count = 1;
    
    while (current && count < position)
    {
        current = current->next;
        count++;
    }
    
    if (current && current->content)
        return (*(int *)current->content);
    return (0);
}

static int get_list_size(t_stack *list)
{
    int size = 0;
    t_stack *current = list;
    
    while (current)
    {
        size++;
        current = current->next;
    }
    return (size);
}

int get_max_value_in_list(t_list *list)
{
    if (!list || !list->content)
        return (0);
    
    int max = *(int *)list->content;
    t_list *current = list->next;
    
    while (current)
    {
        if (current->content && *(int *)current->content > max)
            max = *(int *)current->content;
        current = current->next;
    }
    return (max);
}

int get_min_value_in_list(t_list *list)
{
    if (!list || !list->content)
        return (0);
    
    int min = *(int *)list->content;
    t_list *current = list->next;
    
    while (current)
    {
        if (current->content && *(int *)current->content < min)
            min = *(int *)current->content;
        current = current->next;
    }
    return (min);
}

// Update data->size_a and data->size_b after operations
static void update_sizes(t_ps *data)
{
    if (!data)
        return;
    
    data->size_a = get_list_size(data->stack_a);
    data->size_b = get_list_size(data->stack_b);
}


static void sort_two_chunk(t_ps *data, t_chunk *to_sort)
{
    if (!data || !to_sort || to_sort->size < 2)
        return;

    // Move elements to top of stack A for comparison
    if (to_sort->loc == BOTTOM_A)
    {
        for (int i = 0; i < 2; i++)
        {
            if (move_from_to(data, BOTTOM_A, TOP_A) == 0)
                break;
        }
    }
    else if (to_sort->loc == TOP_B || to_sort->loc == BOTTOM_B)
    {
        for (int i = 0; i < 2; i++)
        {
            if (move_from_to(data, to_sort->loc, TOP_A) == 0)
                break;
        }
    }
    
    // Sort if first element is greater than second
    if (data->stack_a && data->stack_a->next && 
        data->stack_a->content && data->stack_a->next->content)
    {
        int first = *(int *)data->stack_a->content;
        int second = *(int *)data->stack_a->next->content;
        if (first > second)
        {
            sa(data);
            update_sizes(data);
        }
    }
    to_sort->size = 0;
    to_sort->loc = TOP_A;
}

static void sort_one(t_ps *data, t_chunk *to_sort)
{
    if (!data || !to_sort || to_sort->size < 1)
        return;

    // Move single element to top of stack A
    if (to_sort->loc != TOP_A)
        move_from_to(data, to_sort->loc, TOP_A);
    
    to_sort->size = 0;
    to_sort->loc = TOP_A;
}

static void chunk_split(t_ps *data, t_chunk *to_split, t_split_dest *dest)
{
    int pivot_1;
    int pivot_2;
    int max_value;
    int next_value;
    int original_size;

    if (!data || !to_split || !dest || to_split->size <= 0)
        return;

    original_size = to_split->size;
    init_size(&dest->min, &dest->mid, &dest->max);
    set_split_loc(to_split->loc, &dest->min, &dest->mid, &dest->max);
    set_third_pivots(to_split->loc, to_split->size, &pivot_1, &pivot_2);
    max_value = chunk_max_value(data, to_split);
    
    for (int i = 0; i < original_size && to_split->size > 0; i++)
    {
        next_value = chunk_value(data, to_split, 1);
        
        if (next_value > max_value - pivot_2)
        {
            if (move_from_to(data, to_split->loc, dest->max.loc))
            {
                dest->max.size++;
                split_max_reduction(data, &dest->max);
            }
        }
        else if (next_value > max_value - pivot_1)
        {
            if (move_from_to(data, to_split->loc, dest->mid.loc))
                dest->mid.size++;
        }
        else
        {
            if (move_from_to(data, to_split->loc, dest->min.loc))
                dest->min.size++;
        }
        
        to_split->size--;
        update_sizes(data);
        if (a_partly_sort(data, 1) && to_split->size > 0)
            easy_sort(data, to_split);
    }
}

static void init_size(t_chunk *min, t_chunk *mid, t_chunk *max)
{
    if (!min || !mid || !max)
        return;
    min->size = 0;
    mid->size = 0;
    max->size = 0;
}

static void set_split_loc(t_loc loc, t_chunk *min, t_chunk *mid, t_chunk *max)
{
    if (!min || !mid || !max)
        return;

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

static void set_third_pivots(t_loc loc, int crt_size, int *pivot_1, int *pivot_2)
{
    if (!pivot_1 || !pivot_2 || crt_size <= 0)
        return;

    *pivot_2 = crt_size / 3;
    *pivot_1 = 2 * crt_size / 3;
    
    if (loc == TOP_B || loc == BOTTOM_B)
        *pivot_1 = crt_size / 2;
    if ((loc == TOP_A || loc == BOTTOM_A) && crt_size < 15)
        *pivot_1 = crt_size;
    if (loc == BOTTOM_B && crt_size < 8)
        *pivot_2 = crt_size / 2;
}

static void chunk_to_the_top(t_ps *data, t_chunk *to_sort)
{
    if (!data || !to_sort)
        return;
    update_sizes(data);
    if (to_sort->loc == BOTTOM_B && data->size_b == to_sort->size)
        to_sort->loc = TOP_B;
    if (to_sort->loc == BOTTOM_A && data->size_a == to_sort->size)
        to_sort->loc = TOP_A;
}

static void easy_sort(t_ps *data, t_chunk *to_sort)
{
    if (!data || !to_sort)
        return;
    while (to_sort->loc != TOP_A && to_sort->size > 0)
    {
        if (data->stack_a && data->stack_a->content &&
            *(int *)data->stack_a->content == chunk_value(data, to_sort, 1) + 1 
            && to_sort->size > 0)
            sort_one(data, to_sort);
        else if (data->stack_a && data->stack_a->content &&
            *(int *)data->stack_a->content == chunk_value(data, to_sort, 2) + 1 
        	&& to_sort->size > 1)
            easy_sort_second(data, to_sort);
        else
            break;
    }
}

static void easy_sort_second(t_ps *data, t_chunk *to_sort)
{
    if (!data || !to_sort)
        return;

    if (to_sort->loc == TOP_B)
        handle_top_b(data, to_sort);
    else if (to_sort->loc == BOTTOM_A)
        handle_bottom_a(data, to_sort);
    else if (to_sort->loc == BOTTOM_B)
        handle_bottom_b(data, to_sort);
    to_sort->size--;
    update_sizes(data);
}

static void handle_top_b(t_ps *data, t_chunk *to_sort)
{
    if (!data || !to_sort)
        return;

    if (data->stack_b && data->stack_b->content)
    {
        sb(data);
        pa(data);
        if (data->stack_b && data->stack_b->content && 
            data->stack_a && data->stack_a->content &&
            *(int *)data->stack_b->content == *(int *)data->stack_a->content - 1)
        {
            pa(data);
            to_sort->size--;
        }
        update_sizes(data);
    }
}

static void handle_bottom_a(t_ps *data, t_chunk *to_sort)
{
    if (!data || !to_sort)
        return ;
    rra(data);
    rra(data);
    if (data->stack_a && data->stack_a->content)
    {
        sa(data);
        
        if (data->stack_a && data->stack_a->next &&
            data->stack_a->content && data->stack_a->next->content &&
            *(int *)data->stack_a->content == *(int *)data->stack_a->next->content - 1)
            to_sort->size--;
        else
            ra(data);
        update_sizes(data);
    }
}

static void handle_bottom_b(t_ps *data, t_chunk *to_sort)
{
    if (!data || !to_sort)
        return;
    rrb(data);
    rrb(data);
    if (data->stack_b && data->stack_b->content)
    {
        pa(data);   
        if (data->stack_b && data->stack_b->content && 
            data->stack_a && data->stack_a->content &&
            *(int *)data->stack_b->content == *(int *)data->stack_a->content - 1)
        {
            pa(data);
            to_sort->size--;
        }
        else
            rb(data);
        update_sizes(data);
    }
}

static void split_max_reduction(t_ps *data, t_chunk *max)
{
    if (!data || !max)
        return ;
    if (max->loc == TOP_A && max->size == 3 && data->stack_a)
    {
        int a = get_list_element_at_position(data->stack_a, 1);
        int b = get_list_element_at_position(data->stack_a, 2);
        int c = get_list_element_at_position(data->stack_a, 3);
        int d = get_list_element_at_position(data->stack_a, 4);
        
        if (is_consecutive(a, b, c, d) && a_partly_sort(data, 4))
        {
            sort_three_chunk(data, max);
            return ;
        }
    }
    
    if (max->loc == TOP_A && data->stack_a && data->stack_a->content)
    {
        int first = get_list_element_at_position(data->stack_a, 1);
        int third = get_list_element_at_position(data->stack_a, 3);
        
        if (first == third - 1 && a_partly_sort(data, 3))
        {
            sa(data);
            max->size--;
            update_sizes(data);
        }
    }
    
    if (max->loc == TOP_A && a_partly_sort(data, 1))
    {
        max->size--;
        update_sizes(data);
    }
}

static bool a_partly_sort(t_ps *data, int from)
{
    if (!data || !data->stack_a || from <= 0)
        return (false);

    t_stack *current = data->stack_a;
    
    // Skip 'from' elements
    for (int i = 1; i < from && current; i++)
        current = current->next;
    
    if (!current || !current->content)
        return (true);
    
    int prev_value = *(int *)current->content;
    current = current->next;
    
    while (current)
    {
        if (!current->content)
            return (false);
        
        int current_value = *(int *)current->content;
        if (current_value != prev_value + 1)
            return (false);
        prev_value = current_value;
        current = current->next;
    }
    
    return (true);
}

static bool is_consecutive(int a, int b, int c, int d)
{
    // Simple bubble sort for 4 elements
    if (a > b) { int temp = a; a = b; b = temp; }
    if (b > c) { int temp = b; b = c; c = temp; }
    if (c > d) { int temp = c; c = d; d = temp; }
    if (a > b) { int temp = a; a = b; b = temp; }
    if (b > c) { int temp = b; b = c; c = temp; }
    if (a > b) { int temp = a; a = b; b = temp; }
    
    return ((b - a == 1) && (c - b == 1) && (d - c == 1));
}

static void sort_three_chunk(t_ps *data, t_chunk *to_sort)
{
    int max;

    if (!data || !to_sort || to_sort->size < 3)
        return;

    max = chunk_max_value(data, to_sort);
    
    if (to_sort->loc == TOP_A)
        sort_three_top_a(data, to_sort, max);
    else if (to_sort->loc == BOTTOM_A)
        sort_three_bottom_a(data, to_sort, max);
    else if (to_sort->loc == TOP_B)
        sort_three_top_b(data, to_sort, max);
    else if (to_sort->loc == BOTTOM_B)
        sort_three_bottom_b(data, to_sort, max);
}

static void sort_three_top_a(t_ps *data, t_chunk *to_sort, int max)
{
    if (!data || !to_sort || !data->stack_a || !data->stack_a->content)
        return;

    int first = *(int *)data->stack_a->content;
    int second = (data->stack_a->next && data->stack_a->next->content) ? 
                 *(int *)data->stack_a->next->content : 0;

    if (first == max)
    {
        sa(data);
        ra(data);
        sa(data);
        rra(data);
    }
    else if (second == max)
    {
        ra(data);
        sa(data);
        rra(data);
    }
    
    update_sizes(data);
    to_sort->loc = TOP_A;
    to_sort->size = 2;
    sort_two_chunk(data, to_sort);
}

static void sort_three_top_b(t_ps *data, t_chunk *to_sort, int max)
{
    if (!data || !to_sort || !data->stack_b || !data->stack_b->content)
        return;

    pa(data);
    
    if (data->stack_b && data->stack_b->content)
    {
        int first = *(int *)data->stack_b->content;
        int second = (data->stack_b->next && data->stack_b->next->content) ? 
                     *(int *)data->stack_b->next->content : 0;

        if (first == max)
        {
            pa(data);
            sa(data);
        }
        else if (second == max)
        {
            sb(data);
            pa(data);
            sa(data);
        }
        else
        {
            pa(data);
        }
    }
    update_sizes(data);
    to_sort->loc = TOP_A;
    to_sort->size = 2;
    sort_two_chunk(data, to_sort);
}

static void sort_three_bottom_a(t_ps *data, t_chunk *to_sort, int max)
{
    if (!data || !to_sort)
        return;
    rra(data);
    rra(data);
    if (data->stack_a && data->stack_a->content)
    {
        int first = *(int *)data->stack_a->content;
        int second = (data->stack_a->next && data->stack_a->next->content) ? 
                     *(int *)data->stack_a->next->content : 0;
        if (first == max)
        {
            sa(data);
            rra(data);
        }
        else if (second == max)
        {
            rra(data);
        }
        else
        {
            pb(data);
            rra(data);
            sa(data);
            pa(data);
        }
    }
    update_sizes(data);
    to_sort->loc = TOP_A;
    to_sort->size = 2;
    sort_two_chunk(data, to_sort);
}

static void sort_three_bottom_b(t_ps *data, t_chunk *to_sort, int max)
{
    if (!data || !to_sort)
        return;
    rrb(data);
    rrb(data);
    if (data->stack_b && data->stack_b->content)
    {
        int first = *(int *)data->stack_b->content;
        int second = (data->stack_b->next && data->stack_b->next->content) ? 
                     *(int *)data->stack_b->next->content : 0;

        if (first == max)
        {
            pa(data);
            rrb(data);
        }
        else if (second == max)
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
    }
    update_sizes(data);
    to_sort->loc = TOP_A;
    to_sort->size = 2;
    sort_two_chunk(data, to_sort);
}

// Helper functions for chunk operations
int	chunk_max_value(t_ps *data, t_chunk *chunk)
{
	t_stack	*stk;
	int		size;
	int		max_value;
	int		i;

	stk = loc_to_stack(data, chunk->loc);
	size = chunk->size;
	max_value = 0;
	i = 0;
	if (chunk->loc == TOP_A || chunk->loc == TOP_B)
		i = stk->top;
	else if (chunk->loc == BOTTOM_A || chunk->loc == BOTTOM_B)
		i = stk->bottom;
	while (size--)
	{
		if (stk->stack[i] > max_value)
			max_value = stk->stack[i];
		if (chunk->loc == TOP_A || chunk->loc == TOP_B)
			i = calculate_next_down_index(stk, i);
		else if (chunk->loc == BOTTOM_A || chunk->loc == BOTTOM_B)
			i = calculate_next_up_index(stk, i);
	}
	return (max_value);
}

static int chunk_value(t_ps *data, t_chunk *chunk, int position)
{
    if (!data || !chunk || position <= 0)
        return (0);
    if (chunk->loc == TOP_A || chunk->loc == BOTTOM_A)
        return (get_list_element_at_position(data->stack_a, position));
    else
        return (get_list_element_at_position(data->stack_b, position));
}

static int move_from_to(t_ps *data, t_loc from, t_loc to)
{
    if (!data)
        return (0);
    
    // Check if we have elements to move
    if (from == TOP_A && (!data->stack_a || data->size_a == 0))
        return (0);
    if ((from == TOP_B || from == BOTTOM_B) && (!data->stack_b || data->size_b == 0))
        return (0);
    // Execute move operations
    if (from == TOP_A && to == TOP_B)
    {
        pb(data);
        update_sizes(data);
        return (1);
    }
    else if (from == TOP_B && to == TOP_A)
    {
        pa(data);
        update_sizes(data);
        return (1);
    }
    else if (from == BOTTOM_A && to == TOP_A)
    {
        rra(data);
        update_sizes(data);
        return (1);
    }
    else if (from == BOTTOM_B && to == TOP_B)
    {
        rrb(data);
        update_sizes(data);
        return (1);
    }
    else if (from == BOTTOM_A && to == TOP_B)
    {
        rra(data);
        pb(data);
        update_sizes(data);
        return (1);
    }
    else if (from == BOTTOM_B && to == TOP_A)
    {
        rrb(data);
        pa(data);
        update_sizes(data);
        return (1);
    }
    // Add more movement cases as needed
    
    return (0); // Return 0 for failed move
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

static int	calculate_next_up_index(t_stack *stk, int index)
{
	if (index == 0)
		return (stk->capacity - 1);
	return (index - 1);
}

static int	calculate_next_down_index(t_stack *stk, int index)
{
	if (index == stk->capacity - 1)
		return (0);
	return (index + 1);
}


static t_stack	*loc_to_stack(t_ps *data, t_loc loc)
{
	if (loc == TOP_A || loc == BOTTOM_A)
		return (data->stack_a);
	else
		return (data->stack_b);
}