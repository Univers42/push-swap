/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 00:00:00 by backtrack         #+#    #+#             */
/*   Updated: 2025/07/21 16:40:31 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_VISITED 4096

// Forward declarations for internal helpers
static int is_sorted_stack_a(t_ps *data);
static void copy_stack_state(t_ps *dest, t_ps *src);
static void apply_operation(t_ps *data, t_op op);
static int backtrack_solve(t_backtrack_state *state, t_ps *current_data, int depth);
static void execute_best_sequence(t_ps *data, t_move_sequence *sequence);
static int is_operation_useful(t_ps *data, t_op op);


// Helper to check if op undoes prev_op
static int is_undo_op(t_op prev_op, t_op op)
{
	// Only allow non-undoing moves
	if ((prev_op == OP_RA && op == OP_RRA) || (prev_op == OP_RRA && op == OP_RA))
		return 1;
	if ((prev_op == OP_RB && op == OP_RRB) || (prev_op == OP_RRB && op == OP_RB))
		return 1;
	if ((prev_op == OP_PA && op == OP_PB) || (prev_op == OP_PB && op == OP_PA))
		return 1;
	return 0;
}

static uint64_t hash_stack_state(t_ps *data)
{
	uint64_t hash = 0;
	for (int i = 0; i < data->a.element_count; i++)
		hash = hash * 31 + data->a.stack[i];
	for (int i = 0; i < data->b.element_count; i++)
		hash = hash * 17 + data->b.stack[i];
	return hash;
}

/**
 * backtrack_sort - Main backtracking function to find optimal sorting sequence
 * @data: Pointer to the main push_swap data structure
 * @max_size: Maximum number of elements to consider for backtracking
 * 
 * Uses backtracking to find the optimal sequence of moves to sort the stack.
 * This is most effective for small chunks (2-8 elements) where brute force
 * exploration is feasible.
 * 
 * Returns: 1 if solution found and applied, 0 if no solution within depth limit
 */
int backtrack_sort(t_ps *data, int max_size)
{
    if (is_sorted_stack_a(data))
        return (1);

    int total_elements = get_stack_size(&data->a) + get_stack_size(&data->b);
    if (total_elements > max_size || total_elements > 10)
        return (0);

    t_backtrack_state state;
    t_ps temp_data;

    state.original_data = data;
    state.best_sequence.count = 0;
    state.best_sequence.score = INT_MAX;
    state.max_depth = (total_elements <= 3) ? 6 : (total_elements <= 5) ? 12 : (total_elements <= 8) ? 18 : 24;
    state.current_depth = 0;
    state.move_count = 0;

    copy_stack_state(&temp_data, data);

    if (backtrack_solve(&state, &temp_data, 0))
    {
        execute_best_sequence(data, &state.best_sequence);
        // ADD THIS CHECK:
        if (is_sorted_stack_a(data))
            return (1);
        // If not sorted, fallback to legacy code
        return (0);
    }

    return (0);
}

/**
 * backtrack_sort_chunk - Apply backtracking to a specific chunk
 * @data: Pointer to the main push_swap data structure
 * @to_sort: Pointer to the chunk to sort
 * 
 * Integrates backtracking into the chunk-based sorting system.
 * Falls back to existing algorithms if backtracking doesn't find a solution.
 */
void backtrack_sort_chunk(t_ps *data, t_chunk *to_sort)
{
    // Try backtracking first for small chunks
    if (to_sort->size <= 6)
    {
        // Create a temporary state focusing on this chunk
        if (backtrack_sort(data, to_sort->size))
        {
            to_sort->size = 0;  // Mark as sorted
            return;
        }
    }
    
    // Fall back to existing algorithms
    if (to_sort->size == 1)
        sort_one(data, to_sort);
    else if (to_sort->size == 2)
        sort_two(data, to_sort);
    else if (to_sort->size == 3)
        sort_three(data, to_sort);
    else
        fast_sort(data, to_sort);  // For larger chunks
}

static int op_priority[OP_COUNT] = {
	OP_PA, OP_RA, OP_RRA, OP_SA, OP_PB, OP_RB, OP_RRB, OP_SB, OP_SS, OP_RR, OP_RRR
};

/**
 * backtrack_solve - Recursive backtracking function
 * @state: Current backtracking state
 * @current_data: Current stack state
 * @depth: Current recursion depth
 * 
 * Explores all possible move sequences up to max_depth, pruning branches
 * that exceed the current best score.
 */
static int backtrack_solve(t_backtrack_state *state, t_ps *current_data, int depth)
{
	static uint64_t visited[MAX_VISITED];
	static int visited_count = 0;

	// Reset visited for each top-level call
	if (depth == 0)
		visited_count = 0;

	uint64_t h = hash_stack_state(current_data);
	for (int i = 0; i < visited_count; i++)
		if (visited[i] == h)
			return 0;
	if (visited_count < MAX_VISITED)
		visited[visited_count++] = h;

    // Check if we found a solution
    if (is_sorted_stack_a(current_data))
    {
        if (depth < state->best_sequence.score)
        {
            state->best_sequence.count = state->move_count;
            state->best_sequence.score = depth;
            for (int i = 0; i < state->move_count; i++)
                state->best_sequence.moves[i] = state->moves_tried[i];
            return (1);
        }
    }

    if (depth >= state->max_depth || depth >= state->best_sequence.score)
        return (0);

    // Try prioritized operations
    for (int p = 0; p < OP_COUNT; p++)
    {
        int op = op_priority[p];
        if (!is_operation_useful(current_data, (t_op)op))
            continue;
        if (depth > 0 && is_undo_op((t_op)state->moves_tried[depth - 1], (t_op)op))
            continue;
        if (depth > 1 && state->moves_tried[depth - 1] == op && state->moves_tried[depth - 2] == op)
            continue;

        t_ps next_state;
        copy_stack_state(&next_state, current_data);
        apply_operation(&next_state, (t_op)op);

        state->moves_tried[state->move_count] = op;
        state->move_count++;

        if (backtrack_solve(state, &next_state, depth + 1))
            return (1);

        state->move_count--;
    }
    return (0);
}

/**
 * is_sorted_stack_a - Check if stack A is sorted in ascending order
 * @data: Pointer to the push_swap data structure
 * 
 * Returns: 1 if stack A is sorted and stack B is empty, 0 otherwise
 */
static int is_sorted_stack_a(t_ps *data)
{
    if (get_stack_size(&data->b) > 0)
        return (0);
    
    int size = get_stack_size(&data->a);
    if (size <= 1)
        return (1);
    
    for (int i = 1; i < size; i++)
    {
        if (get_items(&data->a, i) > get_items(&data->a, i + 1))
            return (0);
    }
    return (1);
}

/**
 * calculate_state_score - Heuristic function to evaluate how close we are to sorted
 * @data: Pointer to the push_swap data structure
 * 
 * Lower score means closer to sorted state.
 */
int calculate_state_score(t_ps *data)
{
    int score = 0;
    int size_a = get_stack_size(&data->a);
    int size_b = get_stack_size(&data->b);
    
    // Penalty for elements in stack B
    score += size_b * 10;
    
    // Penalty for inversions in stack A
    for (int i = 1; i < size_a; i++)
    {
        if (get_items(&data->a, i) > get_items(&data->a, i + 1))
            score += 5;
    }
    
    return (score);
}

/**
 * copy_stack_state - Deep copy one stack state to another
 * @dest: Destination data structure
 * @src: Source data structure
 */
static void copy_stack_state(t_ps *dest, t_ps *src)
{
	// Copy stack A
	dest->a.top = src->a.top;
	dest->a.bottom = src->a.bottom;
	dest->a.capacity = src->a.capacity;
	dest->a.element_count = src->a.element_count;
	for (int i = 0; i < src->a.capacity; i++)
		dest->a.stack[i] = src->a.stack[i];

	// Copy stack B
	dest->b.top = src->b.top;
	dest->b.bottom = src->b.bottom;
	dest->b.capacity = src->b.capacity;
	dest->b.element_count = src->b.element_count;
	for (int i = 0; i < src->b.capacity; i++)
		dest->b.stack[i] = src->b.stack[i];

	// Copy op_count
	dest->op_count = src->op_count;
}

/**
 * apply_operation - Apply a push_swap operation to the data structure
 * @data: Pointer to the push_swap data structure
 * @op: Operation to apply
 */
static void apply_operation(t_ps *data, t_op op)
{
    switch (op)
    {
        case OP_SA: sa(data); break;
        case OP_SB: sb(data); break;
        case OP_SS: ss(data); break;
        case OP_PA: pa(data); break;
        case OP_PB: pb(data); break;
        case OP_RA: ra(data); break;
        case OP_RB: rb(data); break;
        case OP_RR: rr(data); break;
        case OP_RRA: rra(data); break;
        case OP_RRB: rrb(data); break;
        case OP_RRR: rrr(data); break;
        default: break;
    }
}

/**
 * is_operation_useful - Prune obviously useless operations
 * @data: Current stack state
 * @op: Operation to check
 * 
 * Returns: 1 if operation might be useful, 0 if clearly useless
 */
static int is_operation_useful(t_ps *data, t_op op)
{
    int size_a = get_stack_size(&data->a);
    int size_b = get_stack_size(&data->b);
    
    switch (op)
    {
        case OP_SA:
        case OP_RA:
        case OP_RRA:
            return (size_a >= 2);
        case OP_SB:
        case OP_RB:
        case OP_RRB:
            return (size_b >= 2);
        case OP_SS:
        case OP_RR:
        case OP_RRR:
            return (size_a >= 2 && size_b >= 2);
        case OP_PA:
            return (size_b > 0);
        case OP_PB:
            return (size_a > 0);
        default:
            return (1);
    }
}

/**
 * execute_best_sequence - Execute the best sequence found by backtracking
 * @data: Pointer to the push_swap data structure
 * @sequence: Best sequence to execute
 */
static void execute_best_sequence(t_ps *data, t_move_sequence *sequence)
{
    for (int i = 0; i < sequence->count; i++)
    {
        apply_operation(data, (t_op)sequence->moves[i]);
    }
}

/**
 * enhanced_sort_three_with_backtrack - Enhanced 3-element sort using backtracking
 * @data: Pointer to the main push_swap data structure
 * 
 * Uses backtracking to find the absolute optimal solution for 3 elements,
 * then falls back to the existing sort_three_simple if needed.
 */
void enhanced_sort_three_with_backtrack(t_ps *data)
{
    if (get_stack_size(&data->a) != 3 || get_stack_size(&data->b) != 0)
    {
        sort_three_simple(data);
        return;
    }
    
    if (backtrack_sort(data, 3))
        return;
    
    // Fallback to existing algorithm
    sort_three_simple(data);
}