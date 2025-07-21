/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithms.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:13:26 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/21 15:46:25 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHMS_H
# define ALGORITHMS_H

# include "stack.h"

# define BACKTRACK_SIZE_LIMIT 10
// Forward declarations
typedef struct s_ps		t_ps;

// Chunk structure for chunk sort
typedef struct s_chunk
{
	t_loc	loc;
	int		size;
}	t_chunk;

// Split destination for chunk sort
typedef struct s_split_dest
{
	t_chunk	min;
	t_chunk	mid;
	t_chunk	max;
}	t_split_dest;

// Now you can use t_chunk in arrays:
typedef struct s_chunk_stack
{
    t_chunk chunks[1024];
    int top;
}   t_chunk_stack;

typedef struct s_chunk_locs {
	t_loc min;
	t_loc mid;
	t_loc max;
} t_chunk_locs;

typedef struct s_chunk_pivot_cfg {
	int pivot_1_factor;
	int pivot_2_factor;
	int pivot_1_override;
	int pivot_2_override;
	int pivot_1_min_size;
	int pivot_2_min_size;
} t_chunk_pivot_cfg;

typedef struct s_chunk_fsm {
	t_chunk_locs locs;
	t_chunk_pivot_cfg pivots;
} t_chunk_fsm;

// Algorithm types
typedef enum e_algo_type
{
	ALGO_CHUNK,
	ALGO_GREEDY,
	ALGO_K_SORT,
	ALGO_LIS,
	ALGO_RADIX,
	ALGO_QUEUE
}	t_algo_type;

// Greedy node structure
typedef struct s_greedy_node
{
	int	value;
	int	index;
	int	target_pos;
	int	cost_a;
	int	cost_b;
	int	total_cost;
}	t_greedy_node;

// Maximum depth for backtracking to prevent infinite loops
#define MAX_BACKTRACK_DEPTH 12
#define MAX_MOVES 100

typedef struct s_move_sequence {
    int moves[MAX_MOVES];
    int count;
    int score;
} t_move_sequence;

typedef struct s_backtrack_state {
    t_ps *original_data;
    t_move_sequence best_sequence;
    int max_depth;
    int current_depth;
    int moves_tried[MAX_MOVES];
    int move_count;
} t_backtrack_state;

// Remove this block:
// typedef enum e_operation {
//     OP_SA = 0, OP_SB, OP_SS,
//     OP_PA, OP_PB,
//     OP_RA, OP_RB, OP_RR,
//     OP_RRA, OP_RRB, OP_RRR,
//     OP_COUNT
// } t_operation;

// Instead, define OP_COUNT for backtracking logic:
#define OP_COUNT 11 // Number of operations in t_op (from stack.h)

// Function prototypes

// MAIN ENTRIES ALGORITHM
void		chunk_sort(t_ps *data);
void		greedy_sort(t_ps *data);
void		k_sort(t_ps *data);
void		radix_sort(t_ps *data);
void		lis_sort(t_ps *data);
void		queue_sort(t_ps *data);

// SIMPLE PERMUTATIONS AGORITHMS
void		sort_one(t_ps *data, t_chunk *to_sort);
void		sort_two(t_ps *data, t_chunk *to_sort);
void		sort_three(t_ps *data, t_chunk *to_sort);
void		sort_three_simple(t_ps *data);
void		fast_sort(t_ps *data, t_chunk *to_sort);

//------------------------HELPERS-------------------------------//


// K-based sorting algorithm
void		k_sort(t_ps *data);
int			k_find_min_position(t_ps *data, int size_a, int min_value);

//HELPERS FUNCTIONS FOR SPECIFIC ALGORITHMS
int			chunk_value(t_ps *data, t_chunk *chunk, int n);
int			chunk_max_value(t_ps *data, t_chunk *chunk);
t_stack		*loc_to_stack(t_ps *data, t_loc loc);
int			transfer_chunk(t_ps *data, t_loc from, t_loc to);
void		loc_seg(t_ps *data, t_chunk *to_sort);

// Greedy algorithm helpers
void		execute_move(t_ps *data, t_greedy_node *node);
int			find_target_position(t_ps *data, int value);
int			calculate_total_cost(int cost_a, int cost_b,
				int pos_a, int pos_b);
void		push_element_strategically(t_ps *data,
				int current, int total_size);
void		calculate_costs(t_ps *data, t_greedy_node *nodes,
				int size_b);
void		calculate_move_costs(t_greedy_node *node, int size_a,
				int size_b);
int			find_cheapest(t_greedy_node *nodes, int size);
int			find_min_pos(t_ps *data, int size_a, int min_value);
void		execute_combined_and_remaining(t_ps *data,
				int moves_a, int moves_b, t_greedy_node *node);
void		rotate_to_top(t_ps *data, int min_pos, int size_a);
int			find_min_target(t_ps *data, int size_a);
void		push_to_b(t_ps *data);
void		push_back_to_a(t_ps *data);
void		final_rotation(t_ps *data);
void		rotation_b(t_ps *data, int moves_b, bool rotate_b_up);
void		rotation_a(t_ps *data, int moves_a, bool rotate_a_up);
int			find_best_target(t_ps *data, int value, int size_a);

// K-sort helpers
void		k_sort_handle_small_arrays(t_ps *data);
void		k_sort_apply_final_rotation(t_ps *data);
void		k_sort_push_loop(t_ps *data, int *range,
				int *i, int target_remaining);
void		k_handle_range_expansion(t_ps *data,
				int *range, int *i, int *rotations);
void		k_sort_handle_remaining_in_a(t_ps *data);
void		k_find_and_move_max_to_top(t_ps *data);
void		k_find_max_in_stack_b(t_ps *data, int *max_value,
				int *max_position, int size_b);
void		k_rotate_max_to_top_b(t_ps *data, int max_position,
				int size_b);
void		k_rotate_min_to_top(t_ps *data, int min_pos, int size_a);

// Radix helpers
void		radix_handle_small_arrays(t_ps *data);
void		radix_rotate_to_position(t_ps *data, int min_pos, int size_a);
int			calculate_max_bits_for_size(int size);

// LIS helpers
// LIS-based sorting algorithm
void		lis_print_final_result(bool is_ascending);
void		lis_handle_small_arrays(t_ps *data);
void		lis_push_back_phase(t_ps *data);
void		lis_rotate_max_to_top(t_ps *data, int max_position,
				int size_b);
void		lis_final_rotation_to_sorted(t_ps *data);

void	chunk_sort_loop(t_ps *data, t_chunk *to_sort);

const t_chunk_fsm	*get_chunk_fsm_table(void);

// Backtracking integration
int			backtrack_sort(t_ps *data, int max_size);
void		backtrack_sort_chunk(t_ps *data, t_chunk *to_sort);
void		enhanced_sort_three_with_backtrack(t_ps *data);
int calculate_state_score(t_ps *data);
#endif
