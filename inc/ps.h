/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 16:30:13 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/07 13:46:43 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_H
# define PS_H

# include "libft.h"
# include "stack.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>

# define NEWLINE() (write(1,"\n",1))
# define MAX_OPERATIONS 100000  // Maximum operations buffer size

// Forward declaration of t_ps
typedef struct s_ps t_ps;

// Forward declaration for greedy algorithm
typedef struct s_greedy_node t_greedy_node;

// Chunk algorithm types
typedef enum e_loc
{
    TOP_A,
    BOTTOM_A,
    TOP_B,
    BOTTOM_B
} t_loc;

typedef struct s_chunk
{
    t_loc loc;
    int size;
} t_chunk;

typedef struct s_split_dest
{
    t_chunk min;
    t_chunk mid;
    t_chunk max;
} t_split_dest;

// Add this enum for algorithm types
typedef enum e_algo_type
{
	ALGO_CHUNK,
	ALGO_GREEDY,
	ALGO_K_SORT,
	ALGO_RADIX,
	ALGO_LIS,
	ALGO_QUEUE
}	t_algo_type;

// Algorithm-specific context union
typedef union u_algo_context
{
	struct {
		int chunk_size;
		int n_chunks;
	} chunk;
	
	struct {
		t_greedy_node *nodes;
		int nodes_count;
	} greedy;
	
	struct {
		int k_value;
		int range;
	} k_sort;
	
	struct {
		int max_bits;
		int current_bit;
	} radix;
}	t_algo_context;

// Algorithm state structure
typedef struct s_algo_state
{
	t_algo_type		type;
	t_algo_context	ctx;
	void			(*sort_fn)(t_ps *);  // Now t_ps is forward declared
}	t_algo_state;

// Operations buffer structure
typedef struct s_op_buffer
{
    char    **operations;   // Array of operation strings
    int     count;          // Current number of operations
    int     capacity;       // Maximum capacity
}               t_op_buffer;

// Main push_swap structure definition
struct s_ps
{
    t_stack         stack_a;     // Array-based stack A
    t_stack         stack_b;     // Array-based stack B
    int             total_size;  // Total number of elements
    t_algo_state    algo;        // Algorithm state
    t_op_buffer     op_buffer;   // Operations buffer
    bool            recording;   // Flag to enable/disable recording
};

// Stack operations
void    sa(t_ps *ps);
void    sb(t_ps *ps);
void    ss(t_ps *ps);
void    pa(t_ps *ps);
void    pb(t_ps *ps);
void    ra(t_ps *ps);
void    rb(t_ps *ps);
void    rr(t_ps *ps);
void    rra(t_ps *ps);
void    rrb(t_ps *ps);
void    rrr(t_ps *ps);

// Algorithm functions
void    radix_sort(t_ps *data);
void    sort_three(t_ps *ps);
void    sort_two(t_ps *ps);
void    run_sort_algo(t_ps *data);
void    greedy_sort(t_ps *data);
void    chunk_sort(t_ps *data);
// Chunk-specific sort functions
void	sort_three_top_a(t_ps *data, t_chunk *to_sort, t_stack *stk,
		int max);
void	sort_three_bottom_a(t_ps *data, t_chunk *to_sort, t_stack *stk, int max);
void	sort_three_bottom_b(t_ps *data, t_chunk *to_sort, t_stack *stk, int max);
void	sort_three_top_b(t_ps *data, t_chunk *to_sort, t_stack *stk, int max);

// Chunk algorithm specific functions
void    chunk_split(t_ps *data, t_chunk *to_split, t_split_dest *dest);
void    split_max_reduction(t_ps *data, t_chunk *max);
void    easy_sort(t_ps *data, t_chunk *to_sort);
void    sort_three_complex(t_ps *data, t_chunk *to_sort);
bool    a_partly_sort(t_ps *data, int from);
void    chunk_to_the_top(t_ps *data, t_chunk *to_sort);
bool    is_consecutive(int a, int b, int c, int d);
t_stack *loc_to_stack(t_ps *data, t_loc loc);
int     chunk_max_value(t_ps *data, t_chunk *chunk);
int     chunk_value(t_ps *data, t_chunk *chunk, int n);
int     move_from_to(t_ps *data, t_loc from, t_loc to);

// Utility functions
int     find_max_width(t_stack *stack);
void    print_both_stacks(t_stack *stack_a, t_stack *stack_b);
void    print_stack(t_stack *stack, char name);
void    ft_print_sub_banner(const char *title, const char *subtitle);

// Recorder functions (only available when using micro_test.c)
void    record_operation(const char *operation);
int     is_recording(void);
void    init_recorder(void);
void    start_recording(void);
void    stop_recording(void);
void    cleanup_recorder(void);

// Add algorithm registry functions
void    init_algorithm(t_ps *data, int mode);
void    run_algorithm(t_ps *data);

// Buffer management functions
void    init_op_buffer(t_op_buffer *buffer, int capacity);
void    free_op_buffer(t_op_buffer *buffer);
void    append_operation(t_ps *ps, const char *op);
void    print_operations(t_ps *ps);
void    clear_operations(t_ps *ps);

#endif