/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithms.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:13:26 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 22:57:34 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHMS_H
# define ALGORITHMS_H

# include "stack_core.h"
# include "stack_operations.h"

typedef enum e_loc
{
	TOP_A,
	BOTTOM_A,
	TOP_B,
	BOTTOM_B
}			t_loc;

typedef struct s_chunk
{
	t_loc	loc;
	int		size;
}			t_chunk;

typedef struct s_split_dest
{
	t_chunk	min;
	t_chunk	mid;
	t_chunk	max;
}			t_split_dest;

typedef struct s_turk_node
{
	int	value;
	int	index;
	int	target_pos;
	int	cost_a;
	int	cost_b;
	int	total_cost;
}	t_turk_node;

typedef struct s_greedy_node
{
	int	value;
	int	index;
	int	target_pos;
	int	cost_a;
	int	cost_b;
	int	total_cost;
}	t_greedy_node;

// Main sorting interface
void		sort(t_ps *data);

// Chunk-based sorting
void		chunk_sort(t_ps *data);
void		rec_chunk_sort(t_ps *data, t_chunk *to_sort);
void		chunk_split(t_ps *data, t_chunk *to_split, t_split_dest *dest);

// Small array optimizations
void		sort_one(t_ps *data, t_chunk *to_sort);
void		sort_two(t_ps *data, t_chunk *to_sort);
void		sort_three(t_ps *data, t_chunk *to_sort);

// Chunk utilities
int			chunk_value(t_ps *data, t_chunk *chunk, int n);
int			chunk_max_value(t_ps *data, t_chunk *chunk);
t_stack		*loc_to_stack(t_ps *data, t_loc loc);

// Element movement
int			move_from_to(t_ps *data, t_loc from, t_loc to);

// Greedy algorithm implementation
void		greedy_sort(t_ps *data);
void		sort_three_simple(t_ps *data);
int			find_min_value_in_stack(t_stack *stack);
void		greedy_execute_move(t_ps *data, t_greedy_node *node);
int			greedy_find_target_position(t_ps *data, int value);
int			greedy_calculate_total_cost(int cost_a, int cost_b, int pos_a,
				int pos_b);
void		greedy_push_element_strategically(t_ps *data, int current,
				int total_size);
void		greedy_calculate_costs(t_ps *data, t_greedy_node *nodes,
				int size_b);
void		greedy_calculate_move_costs(t_greedy_node *node, int size_a,
				int size_b);
int			greedy_find_cheapest(t_greedy_node *nodes, int size);
int			greedy_find_min_pos(t_ps *data, int size_a, int min_value);
void		greedy_execute_combined_and_remaining(t_ps *data, int moves_a,
				int moves_b, t_greedy_node *node);
void		greedy_rotate_to_top(t_ps *data, int min_pos, int size_a);
int			greedy_find_best_target(t_ps *data, int value, int size_a);
int			greedy_find_min_target(t_ps *data, int size_a);

// K-based sorting algorithm
void		k_sort(t_ps *data);
void		k_sort_apply_final_rotation(t_ps *data);
void		k_sort_verify_order(t_ps *data, int total_size);
void		k_sort_handle_small_arrays(t_ps *data);
void		k_sort_print_debug_info(t_ps *data, int total_size);
void		k_sort_push_loop(t_ps *data, int *range, int *i,
				int target_remaining);
void		k_handle_range_expansion(t_ps *data, int *range, int *i,
				int *rotations);
void		k_sort_handle_remaining_in_a(t_ps *data);
void		k_find_and_move_max_to_top(t_ps *data);
void		k_find_max_in_stack_b(t_ps *data, int *max_value, int *max_position,
				int size_b);
void		k_rotate_max_to_top_b(t_ps *data, int max_position, int size_b);
int			k_find_min_position(t_ps *data, int size_a, int min_value);
void		k_rotate_min_to_top(t_ps *data, int min_pos, int size_a);

// Radix sorting algorithm
void		radix_sort(t_ps *data);
void		radix_handle_small_arrays(t_ps *data);
void		radix_debug_bit_pass(int bit_position);
void		radix_rotate_to_position(t_ps *data, int min_pos, int size_a);
void		radix_debug_final_verification(t_ps *data, int total_size);
void		radix_debug_first_elements(t_ps *data, int total_size);
void		radix_debug_check_order(t_ps *data, int total_size);
void		radix_debug_break_point(int position, int current, int next);
void		radix_debug_final_result(bool is_ascending);
int			calculate_max_bits_for_size(int size);
// LIS-based sorting algorithm
void		lis_sort(t_ps *data);
void		lis_handle_small_arrays(t_ps *data);
void		lis_push_back_phase(t_ps *data);
void		lis_rotate_max_to_top(t_ps *data, int max_position, int size_b);
void		lis_print_final_result(bool is_ascending);
void		lis_push_phase(t_ps *data, int range, int total_size);
void		lis_sort_remaining_in_a(t_ps *data);
void		lis_verify_final_rotation(t_ps *data);
void		lis_final_rotation_to_sorted(t_ps *data);
void		lis_handle_single_rotation(t_ps *data, int *range, int total_size);
void		lis_debug_first_elements(t_ps *data, int total_size);
void		lis_debug_check_order(t_ps *data, int total_size);
int			ft_sqrt_simple(int nb);

// Debug mode (stateless - no global variables)
void		set_debug_mode(int mode);
bool		is_debug_mode_enabled(void);
bool		is_verbose_mode_enabled(void);
bool		is_stats_mode_enabled(void);
const char	*get_debug_level_name(int mode);
void		debug_print_stack_state(t_ps *data, const char *context);

// Legacy compatibility
void		enable_debug_mode(void);
void		alternative_sort(t_ps *data);

// Queue-based sorting algorithm
void		queue_sort(t_ps *data);

// Main utilities
void		print_algorithm_name(int mode);

#endif
