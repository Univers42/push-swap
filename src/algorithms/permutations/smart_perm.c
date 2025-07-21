
#include "push_swap.h"
#include "algorithms.h"
#include "backtrack.h"
/**
 * smart_sort_one - Enhanced single element sorting with backtracking consideration
 * @data: Pointer to the main push_swap data structure
 * @to_sort: Pointer to the chunk to sort
 * 
 * For single elements, backtracking might find a more efficient path considering
 * the global state of both stacks.
 */
void smart_sort_one(t_ps *data, t_chunk *to_sort)
{
    // For single elements, try backtracking if it might be beneficial
    if (is_chunk_worth_backtracking(to_sort))
    {
        t_ps backup_data;
        backup_data = *data;  // Simple backup
        
        if (backtrack_sort(data, 3))  // Consider context of nearby elements
        {
            to_sort->size = 0;
            return;
        }
        
        // Restore if backtracking failed
        *data = backup_data;
    }
    
    // Fallback to original algorithm
    sort_one(data, to_sort);
}

/**
 * smart_sort_two - Enhanced two-element sorting with backtracking
 * @data: Pointer to the main push_swap data structure
 * @to_sort: Pointer to the chunk to sort
 * 
 * Uses backtracking to find optimal 2-element sorting considering global state.
 */
void smart_sort_two(t_ps *data, t_chunk *to_sort)
{
    // Always try backtracking for 2-element chunks
    if (backtrack_sort(data, 4))  // Consider broader context
    {
        to_sort->size = 0;
        return;
    }
    
    // Fallback to original algorithm
    sort_two(data, to_sort);
}

/**
 * smart_sort_three - Enhanced three-element sorting with backtracking
 * @data: Pointer to the main push_swap data structure
 * @to_sort: Pointer to the chunk to sort
 * 
 * Uses backtracking to find the absolute optimal solution for 3 elements.
 */
void smart_sort_three(t_ps *data, t_chunk *to_sort)
{
    // Try backtracking first - it's very effective for 3 elements
    if (backtrack_sort(data, 5))  // Consider some context
    {
        to_sort->size = 0;
        return;
    }
    
    // Fallback to original algorithm
    sort_three(data, to_sort);
}

/**
 * smart_fast_sort - Enhanced fast sort with backtracking for small chunks
 * @data: Pointer to the main push_swap data structure
 * @to_sort: Pointer to the chunk to sort
 * 
 * For chunks up to 6 elements, tries backtracking before falling back to fast_sort.
 */
void smart_fast_sort(t_ps *data, t_chunk *to_sort)
{
    // Try backtracking for small chunks where it's feasible
    if (to_sort->size <= 6 && is_chunk_worth_backtracking(to_sort))
    {
        if (backtrack_sort(data, to_sort->size + 2))  // Small context window
        {
            to_sort->size = 0;
            return;
        }
    }
    
    // Fallback to original algorithm
    fast_sort(data, to_sort);
}

/**
 * is_chunk_worth_backtracking - Determine if a chunk benefits from backtracking
 * @to_sort: Pointer to the chunk to evaluate
 * 
 * Returns: 1 if backtracking likely beneficial, 0 otherwise
 */
int is_chunk_worth_backtracking(t_chunk *to_sort)
{
    // Backtracking is most beneficial for small chunks
    if (to_sort->size <= 6)
        return (1);
    
    // For larger chunks, only if they're in awkward positions
    if (to_sort->loc == BOTTOM_B || to_sort->loc == BOTTOM_A)
        return (1);
    
    return (0);
}

/**
 * estimate_backtrack_benefit - Estimate if backtracking will help
 * @data: Pointer to the main push_swap data structure
 * @to_sort: Pointer to the chunk to evaluate
 * 
 * Returns: Estimated benefit score (higher = more beneficial)
 */
int estimate_backtrack_benefit(t_ps *data, t_chunk *to_sort)
{
    int benefit = 0;
    
    // Small chunks always benefit
    if (to_sort->size <= 3)
        benefit += 10;
    else if (to_sort->size <= 6)
        benefit += 5;
    
    // Chunks in awkward positions benefit more
    if (to_sort->loc == BOTTOM_B || to_sort->loc == BOTTOM_A)
        benefit += 3;
    
    // If there are many elements, backtracking can find better global optimums
    int total_elements = get_stack_size(&data->a) + get_stack_size(&data->b);
    if (total_elements <= 8)
        benefit += 5;
    
    return (benefit);
}

/**
 * adaptive_sort_dispatch - Main dispatcher that chooses between algorithms
 * @data: Pointer to the main push_swap data structure
 * @to_sort: Pointer to the chunk to sort
 * 
 * This replaces calls to the original sorting functions throughout your codebase.
 * It intelligently chooses between backtracking and traditional algorithms.
 */
void adaptive_sort_dispatch(t_ps *data, t_chunk *to_sort)
{
    if (to_sort->size == 0)
        return;
    
    // Determine the best approach based on chunk characteristics
    int backtrack_benefit = estimate_backtrack_benefit(data, to_sort);
    
    if (backtrack_benefit >= 8 && to_sort->size <= BACKTRACK_SIZE_LIMIT)
    {
        // High benefit: try backtracking first
        if (backtrack_sort_chunk)
        {
            backtrack_sort_chunk(data, to_sort);
            return;
        }
    }
    
    // Route to appropriate traditional algorithm
    if (to_sort->size == 1)
        sort_one(data, to_sort);
    else if (to_sort->size == 2)
        sort_two(data, to_sort);
    else if (to_sort->size == 3)
        sort_three(data, to_sort);
    else
        fast_sort(data, to_sort);
}

/**
 * global_backtrack_optimization - Apply backtracking to the entire problem
 * @data: Pointer to the main push_swap data structure
 * 
 * This can be called at the beginning to see if the entire problem can be
 * solved optimally with backtracking.
 */
int global_backtrack_optimization(t_ps *data)
{
    int total_elements = get_stack_size(&data->a) + get_stack_size(&data->b);
    
    // Only attempt global backtracking for very small problems
    if (total_elements <= 6)
    {
        return (backtrack_sort(data, total_elements));
    }
    
    return (0);
}

/**
 * selective_backtrack_by_position - Apply backtracking based on stack positions
 * @data: Pointer to the main push_swap data structure
 * @chunk_locations: Array of chunk locations to prioritize
 * @count: Number of locations
 * 
 * Applies backtracking selectively to chunks in specific positions.
 */
void selective_backtrack_by_position(t_ps *data, t_chunk *chunks, int chunk_count)
{
    for (int i = 0; i < chunk_count; i++)
    {
        t_chunk *current = &chunks[i];
        
        // Prioritize bottom chunks and small chunks for backtracking
        if ((current->loc == BOTTOM_A || current->loc == BOTTOM_B) 
            && current->size <= 5)
        {
            if (backtrack_sort(data, current->size + 1))
            {
                current->size = 0;  // Mark as handled
            }
        }
    }
}