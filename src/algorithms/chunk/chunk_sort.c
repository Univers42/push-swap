/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 01:45:11 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/22 02:10:28 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"


/**
 * @brief Main entry for chunk-based sorting.
 *
 * This function decides if the stack is small enough for a simple sort,
 * or if it should use the chunk algorithm. For small stacks (<=3), it
 * sorts directly. For larger stacks, it checks if already sorted, then
 * launches the chunk_sort_loop.
 *
 * Example:
 *   Input: A = [4, 2, 3, 1]
 *   chunk_sort(data)
 *   Output: A = [1, 2, 3, 4]
 *
 * Importance: This is the orchestrator for the chunk sorting process.
 */
void	chunk_sort(t_ps *data)
{
	if (data->total_size <= 3)
	{
		if (data->total_size == 3)
			sort_three_simple(data);
		else if (data->total_size == 2)
		{
			if (get_items(&data->a, 1)
				> get_items(&data->a, 2))
				sa(data);
		}
		return ;
	}
	if (is_stack_sorted(data))
		return ;
	chunk_sort_loop(data, &data->algo_ctx.u_ctx.s_chunk.current_chunk);
}

/**
 * @brief Pushes a chunk onto the chunk stack.
 *
 * Helper for managing the stack of chunks to process. Used in the chunk_sort_loop
 * to keep track of sub-chunks that need further sorting.
 *
 * Example:
 *   stack.top = 0;
 *   push_chunk(&stack, chunk);
 */
static void	push_chunk(t_chunk_stack *stack, t_chunk chunk)
{
	if (stack->top < 1024)
		stack->chunks[stack->top++] = chunk;
}

/**
 * @brief Pops a chunk from the chunk stack.
 *
 * Helper for retrieving the next chunk to process in chunk_sort_loop.
 * Returns 1 if a chunk was popped, 0 if stack is empty.
 *
 * Example:
 *   t_chunk c;
 *   int ok = pop_chunk(&stack, &c);
 */
static int	pop_chunk(t_chunk_stack *stack, t_chunk *out)
{
	if (stack->top > 0)
	{
		*out = stack->chunks[--stack->top];
		return (1);
	}
	return (0);
}

/**
 * @brief Main loop for chunk-based sorting.
 *
 * This function manages the recursive chunk splitting and sorting.
 * It uses a stack to process chunks in a depth-first manner.
 * For each chunk:
 *   - Moves the chunk to the top of the stack (loc_seg)
 *   - If small (<=3), sorts directly (sort_three, sort_two, sort_one)
 *   - Otherwise, divides the chunk into sub-chunks (divide_seg)
 *   - Pushes sub-chunks onto the stack for further processing
 *
 * Example trace:
 *   Initial: A = [8, 7, 6, 5, 4, 3, 2, 1]
 *   chunk_sort_loop(data, &chunk)
 *   - chunk = [8,7,6,5,4,3,2,1]
 *   - divide into [8,7,6], [5,4,3], [2,1]
 *   - sort each sub-chunk recursively
 *   - result: A = [1,2,3,4,5,6,7,8]
 *
 * Importance: This is the core logic of the chunk algorithm.
 */
void	chunk_sort_loop(t_ps *data, t_chunk *to_sort)
{
	t_chunk_stack	stack;
	t_split_dest	dest;
	t_chunk			current;

	stack.top = 0;
	push_chunk(&stack, *to_sort);
	while (pop_chunk(&stack, &current))
	{
		(loc_seg(data, &current), fast_sort(data, &current));
		if (current.size <= 3)
		{
			if (current.size == 3)
				sort_three(data, &current);
			else if (current.size == 2)
				sort_two(data, &current);
			else if (current.size == 1)
				sort_one(data, &current);
			continue ;
		}
		divide_seg(data, &current, &dest);
		push_chunk(&stack, dest.min);
		push_chunk(&stack, dest.mid);
		push_chunk(&stack, dest.max);
	}
}

/**
 * @brief Returns the stack pointer for a given location.
 *
 * Helper function to map a t_loc enum (TOP_A, BOTTOM_A, etc) to the
 * corresponding stack pointer in the t_ps structure.
 *
 * Example:
 *   loc_to_stack(data, TOP_A) -> &data->a
 *   loc_to_stack(data, TOP_B) -> &data->b
 *
 * Importance: Helper for chunk and value access.
 */
t_stack	*loc_to_stack(t_ps *data, t_loc loc)
{
	if (loc == TOP_A || loc == BOTTOM_A)
		return (&data->a);
	else
		return (&data->b);
}

/**
========================================================================
CHUNK_SORT_LOOP: DETAILED BLOCK-BY-BLOCK EXPLANATION
========================================================================
 * This function is the core iterative engine of the chunk sorting algorithm.
 * It processes chunks in a stack-based manner, splitting large chunks into
 * smaller ones until all chunks are small enough to be sorted directly.
 * 
========================================================================
 BLOCK 1: INITIALIZATION
========================================================================
 * 
    * PURPOSE: Set up the processing infrastructure
    * - stack: Manages chunks in LIFO order (Last In, First Out)
    * - dest: Will store min/mid/max subchunks after each split
    * - current: Working variable for the chunk being processed
    * - stack.top = 0: Empty stack ready to receive chunks
	*
 *
=================================================================
BLOCK 2: SEED THE PROCESSING STACK
=================================================================
 *
	* PURPOSE: Start the processing loop
    * - Takes the initial chunk (entire unsorted segment) 
	* 			and pushes it onto stack
    * - This is the "seed" that begins the entire sorting process
    * - After this, stack contains exactly one chunk to process
    * 
    * EXAMPLE: If to_sort represents [5,2,8,1,9,3] with size=6, loc=TOP_A,
    *          the stack now contains this single chunk ready for processing
 *
========================================================================
BLOCK 3: MAIN PROCESSING LOOP
========================================================================
 *
	* PURPOSE: Process chunks until stack is empty
    * - pop_chunk() removes top chunk from stack and stores in 'current'
    * - Returns 1 if successful (chunk retrieved), 0 if stack empty
    * - Loop continues as long as there are chunks to process
    * 
    * BEHAVIOR:
    * - Stack starts with 1 chunk (the original)
    * - Each large chunk splits into 3 smaller chunks (net +2 chunks)
    * - Small chunks (≤3) are sorted and removed (net -1 chunk)
    * - Eventually all chunks become ≤3, stack empties, loop ends
 *
====================================================================
BLOCK 4: PRE-PROCESSING OPTIMIZATIONS
====================================================================
 *
    * PURPOSE: Apply optimizations before main processing
    * 
    * loc_seg(data, &current):
    * - Updates chunk location if it has effectively moved
    * - Example: If chunk was at BOTTOM_A but now entire stack A is this chunk,
    *   location updates to TOP_A for more efficient access
    * - Ensures chunk addressing remains accurate as stacks change
    * 
    * fast_sort(data, &current):
    * - Checks if chunk is already sorted or nearly sorted
    * - If so, applies quick sorting without splitting
    * - Optimization to avoid unnecessary work on already-ordered data
    * 
    * COMMA OPERATOR: Both functions execute in sequence
    * This is a performance optimization block that runs
	* before every chunk process
  *
====================================================================
BLOCK 5: BASE CASE - DIRECT SORTING
====================================================================
  *
    * PURPOSE: Handle chunks small enough for direct sorting
    * 
    * CONDITION: current.size <= 3
    * - These chunks are small enough to sort without further splitting
    * - Direct sorting is more efficient than splitting for tiny chunks
    * 
    * SIZE-SPECIFIC SORTING:
    * - size == 3: Uses specialized 3-element sorting (likely optimized)
    * - size == 2: Simple comparison and swap if needed
    * - size == 1: Single element is already "sorted"
	* d(no-op or position adjustment)
    * 
    * CONTINUE STATEMENT:
    * - Skips the splitting logic below
    * - Moves to next iteration to pop another chunk
    * - This chunk is now fully sorted and won't be split further
    * 
    * EXAMPLE: If current chunk is [7,3,9] at TOP_B:
    * - sort_three() will arrange it as [3,7,9] or proper order for location
    * - Chunk processing is complete for this segment
  *
====================================================================
BLOCK 6: RECURSIVE CASE - CHUNK SPLITTING
====================================================================
  *
    * PURPOSE: Split large chunks into smaller subchunks
    * 
    * divide_seg(data, &current, &dest):
    * - Performs three-way split of current chunk
    * - Uses pivot-based partitioning to create min/mid/max subchunks
    * - Moves elements to appropriate stack locations based on FSM rules
    * - Updates dest.min, dest.mid, dest.max with resulting subchunk info
    * 
    * EXAMPLE SPLIT: If current chunk [15,3,22,8,25,1,18] (size=7):
    * - Calculate pivots based on chunk location and size
    * - Suppose max_value=25, pivot_1=14, pivot_2=7
    * - Elements > 18 (25-7) go to dest.max: [22,25] 
    * - Elements > 11 (25-14) go to dest.mid: [15,18]
    * - Elements ≤ 11 go to dest.min: [3,8,1]
    * 
    * PUSH OPERATIONS:
    * - push_chunk(&stack, dest.min): Add min subchunk to processing stack
    * - push_chunk(&stack, dest.mid): Add mid subchunk to processing stack  
    * - push_chunk(&stack, dest.max): Add max subchunk to processing stack
    * 
    * STACK GROWTH:
    * - Started iteration with 1 chunk (current)
    * - End iteration with 3 new chunks on stack
    * - Net effect: +2 chunks to process
    * - Each subchunk will be processed in future loop iterations
    * 
    * PROCESSING ORDER:
    * - Stack is LIFO, so dest.max processes first, then dest.mid, then
	* 	dest.min
    * - This order is carefully chosen to maintain proper sorting flow
  *
========================================================================
LOOP TERMINATION AND COMPLETION
========================================================================
  * 
	* The loop terminates when pop_chunk() returns 0 (empty stack),
	* which happens when:
	* 1. All original chunks have been split into subchunks ≤ 3 elements
	* 2. All small chunks have been directly sorted
	* 3. No more chunks remain on the processing stack
	* 
	* AT THIS POINT:
	* - Every element in the original unsorted segment has been processed
	* - All chunks of size ≤ 3 have been sorted in their proper locations
	* - The FSM-guided placement ensures proper global ordering
	* - The sorting operation is complete for the entire segment
	* 
	* EXAMPLE COMPLETE EXECUTION:
	* 
	* Initial: Stack=[chunk(size=10)]
	* Iteration 1: Pop chunk(10) → Split → Stack=[max(3), mid(3), min(4)]
	* Iteration 2: Pop max(3) → Direct sort → Stack=[mid(3), min(4)]
	* Iteration 3: Pop mid(3) → Direct sort → Stack=[min(4)]
	* Iteration 4: Pop min(4) → Split → Stack=[max(1), mid(1), min(2)]
	* Iteration 5: Pop max(1) → Direct sort → Stack=[mid(1), min(2)]
	* Iteration 6: Pop mid(1) → Direct sort → Stack=[min(2)]
	* Iteration 7: Pop min(2) → Direct sort → Stack=[]
	* Iteration 8: pop_chunk() returns 0 → Loop exits
	* 
  * Result: All elements sorted and properly positioned
============================================================================
ALGORITHM COMPLEXITY AND CHARACTERISTICS
============================================================================
 * 
 * TIME COMPLEXITY:
 * - Each chunk splits into 3 subchunks → O(log n) depth
 * - Each element processed once per level → O(n log n) total
 * 
 * SPACE COMPLEXITY:
 * - Stack depth is O(log n) in typical cases
 * - Maximum stack size roughly 3^(log n) but pruned by direct sorts
 * 
 * TERMINATION GUARANTEE:
 * - Each split reduces maximum chunk size
 * - Chunks ≤ 3 are terminal cases (no further splits)
 * - Finite input guarantees finite processing
 * 
 * KEY DESIGN DECISIONS:
 * - Iterative (not recursive) to avoid stack overflow
 * - LIFO processing order optimized for cache locality
 * - Pre-processing optimizations reduce unnecessary work
 * - Size-based direct sorting provides efficient base cases
*/
