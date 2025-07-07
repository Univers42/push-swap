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

// Color definitions for printing
//# define RESET "\033[0m"
//# define BOLD "\033[1m"
//# define DIM "\033[2m"
//# define CYAN "\033[36m"
//# define YELLOW "\033[33m"
//# define BRIGHT_YELLOW "\033[93m"
//# define BLUE "\033[34m"
//# define BRIGHT_GREEN "\033[92m"
//# define BRIGHT_MAGENTA "\033[95m"
//# define MAGENTA "\033[35m"

typedef struct s_ps
{
    t_stack  *stack_a;
    t_stack  *stack_b;
    int     size_a;
    int     size_b;
    int     total_size;
}               t_ps;

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

// Utility functions
int     find_max_width(t_stack *stack);
void    print_both_stacks(t_stack *stack_a, t_stack *stack_b);
void    print_stack(t_stack *stack, char name);
int     count_stack_elements(t_stack *stack);
void    ft_print_sub_banner(const char *title, const char *subtitle);
int     is_sorted(t_stack *stack);
int     get_stack_size(t_stack *stack);
int     get_max_value(t_stack *stack);
int     get_min_value(t_stack *stack);
int     find_min_position(t_stack *stack);
t_stack  *create_int_node(int value);

// Recorder functions (only available when using micro_test.c)
void    record_operation(const char *operation);
int     is_recording(void);
void    init_recorder(void);
void    start_recording(void);
void    stop_recording(void);
void    cleanup_recorder(void);
void    ft_stkclear(t_stack **stk);
// Function pointer type for moves
typedef void (*move)(t_ps *ps);

#endif