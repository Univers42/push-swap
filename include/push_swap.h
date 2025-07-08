/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:20:48 by ugerkens          #+#    #+#             */
/*   Updated: 2025/06/16 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <stdint.h>
# include "../libft/libft.h"

// Constants
# define INITIAL_OP_CAPACITY 100
# define HASH_TABLE_THRESHOLD 1000000
# define MAX_OPERATIONS 10000

// Forward declarations
typedef struct s_ps t_ps;

// Stack structure - must be defined before it's used in other structs
typedef struct s_stack
{
	int	*stack;
	int	top;
	int	bottom;
	int	capacity;
	int	element_count;
}	t_stack;

// Enumerations
typedef enum e_op
{
	OP_NULL,
	OP_PA,
	OP_PB,
	OP_RA,
	OP_RB,
	OP_RR,
	OP_RRA,
	OP_RRB,
	OP_RRR,
	OP_SA,
	OP_SB,
	OP_SS
}	t_op;

typedef enum e_loc
{
	TOP_A,
	BOTTOM_A,
	TOP_B,
	BOTTOM_B
}	t_loc;

typedef enum e_algo_type
{
	ALGO_CHUNK,
	ALGO_GREEDY,
	ALGO_K_SORT,
	ALGO_RADIX,
	ALGO_LIS,
	ALGO_QUEUE
}	t_algo_type;


// Algorithm-specific data structures
typedef struct s_chunk
{
	t_loc	loc;
	int		size;
}	t_chunk;

typedef struct s_split_dest
{
	t_chunk	min;
	t_chunk	mid;
	t_chunk	max;
}	t_split_dest;

typedef struct s_greedy_node
{
	int	value;
	int	index;
	int	target_pos;
	int	cost_a;
	int	cost_b;
	int	total_cost;
}	t_greedy_node;

// Polymorphic algorithm context
typedef union u_algo_context
{
	struct {
		t_chunk		current_chunk;
		t_split_dest	split;
	} chunk;
	
	struct {
		t_greedy_node	*nodes;
		int				nodes_count;
		int				phase;  // 0: push to B, 1: push to A
	} greedy;
	
	struct {
		int	k_value;
		int	range;
		int	i;
		int	target_remaining;
	} k_sort;
	
	struct {
		int	max_bits;
		int	current_bit;
	} radix;
	
	struct {
		int	range;
		int	phase;
	} lis;
}	t_algo_context;

// Algorithm state
typedef struct s_algo_state
{
	t_algo_type		type;
	t_algo_context	ctx;
	void			(*sort_fn)(t_ps *);
	const char		*name;
}	t_algo_state;

// Operations buffer
typedef struct s_op_buffer
{
	char	**operations;
	int		count;
	int		capacity;
}	t_op_buffer;

typedef struct s_stack t_stack;
// Main push_swap structure
struct s_ps
{
	t_stack			a;
	t_stack			b;
	t_list			*op_list;
	int				op_count;
	int				op_capacity;
	int				total_size;
	t_algo_state	algo;
	t_op_buffer		op_buffer;
	bool			recording;
};

// Core functions
void		initialize_push_swap_data(t_ps *data, int argc, char **argv);
void		cleanup_and_exit_with_error(t_ps *data);
void		release_allocated_memory(t_ps *data);

// Stack operations
void		allocate_and_init_stack(t_ps *data, t_stack *stk, int capacity);
void		populate_stack_with_ranks(t_ps *data, t_stack *stk, int size, char **arg);
void		convert_numbers_to_ranks(int *numbers, int *rank, int size);

// Basic operations
void		pa(t_ps *data);
void		pb(t_ps *data);
void		sa(t_ps *data);
void		sb(t_ps *data);
void		ss(t_ps *data);
void		ra(t_ps *data);
void		rb(t_ps *data);
void		rr(t_ps *data);
void		rra(t_ps *data);
void		rrb(t_ps *data);
void		rrr(t_ps *data);

// Operation management
void		save_op(t_ps *data, t_op op);
void		increment_op_count(t_ps *data);
void		print_operations(t_list *head);
const char	*op_to_string(t_op op);
t_op		op_from(t_list *node);

// Parser functions
bool		verify_stack_is_sorted(t_ps *data);
bool		validate_numeric_argument(char *arg);
bool		detect_duplicates_optimized(t_ps *data, int *numbers, int size);
bool		detect_duplicates_with_sorting(int *numbers, int size);
void		efficient_sort(int *arr, int size);

// Utility functions
int			get_stack_element_at_position(t_stack *stk, int position);
int			get_current_stack_size(t_stack *stk);
int			calculate_next_up_index(t_stack *stk, int index);
int			calculate_next_down_index(t_stack *stk, int index);
bool		check_if_stack_is_full(t_stack *stk);
bool		check_if_stack_is_empty(t_stack *stk);

// Algorithm selection and execution
void		select_algorithm(t_ps *data, t_algo_type type);
void		execute_algorithm(t_ps *data);
void		sort(t_ps *data);

// Algorithm implementations
void		chunk_sort(t_ps *data);
void		greedy_sort(t_ps *data);
void		k_sort(t_ps *data);
void		radix_sort(t_ps *data);
void		lis_sort(t_ps *data);
void		queue_sort(t_ps *data);

// Small array optimizations
void		sort_three_simple(t_ps *data);
int			find_min_value_in_stack(t_stack *stack);

// Optimization functions
void		post_sort_optimization(t_ps *data);
void		eliminate_neutral_op(t_ps *data);
void		merge_op(t_ps *data);
t_op		neutral_op(t_op op);
void		remove_op_from_list(t_list **list, t_list *to_remove);

// Math utilities
void		ft_swap(void *a, void *b, size_t size);
void		quick_sort_int(int *arr, int low, int high);
int			ft_sqrt(int nb);
int	k_find_min_position(t_ps *data, int size_a, int min_value);
void	k_rotate_max_to_top_b(t_ps *data, int max_position, int size_b);
void	k_rotate_min_to_top(t_ps *data, int min_pos, int size_a);
void	k_find_max_in_stack_b(t_ps *data, int *max_value, int *max_position,
		int size_b);
#endif
