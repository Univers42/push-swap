/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:20:48 by ugerkens          #+#    #+#             */
/*   Updated: 2025/07/18 16:25:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

// System headers
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>

// Library headers
# include "libft.h"
# include "algorithms.h"
// Project headers (order matters to avoid circular dependencies)
# include "stack.h"
// Include other headers after main structure is defined
# include "parser.h"
# include "utils.h"
# include "ctrl_station.h"
# include "optimizations.h"
# include "tracker.h"

// Algorithm context structure
typedef struct s_algo_context
{
	union
	{
		struct
		{
			t_chunk			current_chunk;
			t_split_dest	split_dest;
		}	s_chunk;
		struct
		{
			t_greedy_node	*nodes;
			int				nodes_count;
			int				phase;
		}	s_greedy;
		struct
		{
			int	k_value;
			int	range;
		}	s_k_sort;
		struct
		{
			int	bit_count;
			int	max_bits;
		}	s_radix;
		struct
		{
			int	*lis;
			int	lis_length;
		}	s_lis;
		struct
		{
			int	dummy;
		}	s_queue;
	}	u_ctx;
}	t_algo_context;

// Algorithm structure
typedef struct s_algorithm
{
	void			(*sort_fn)(t_ps *);
	void			(*init_fn)(t_ps *);
	const char		*name;
}	t_algorithm;

// Main push_swap structure - define the actual structure
typedef struct s_ps
{
	t_stack			a;
	t_stack			b;
	t_list			*op_list;
	int				op_count;
	int				op_capacity;
	int				total_size;
	t_algorithm		algo;
	t_algo_context	algo_ctx;
}					t_ps;
// Function pointer types
typedef void	(*t_config_fn)(t_ps *data);

// CORE INITIALIZATION
void		init_engine_ps(t_ps *data, int argc, char **argv);
void		allocate_and_init_stack(t_ps *data, t_stack *stk, int capacity);
void config_mask(t_ps *data, void (*ctx_alg)(t_ps *),
					void (*init)(t_ps *), t_string name);
void		config_queue(t_ps *data);
void		config_lis(t_ps *data);
void		config_radix(t_ps *data);
void		config_k_sort(t_ps *data);
void		config_greedy(t_ps *data);
void		config_chunk(t_ps *data);
void		init_chunk_context(t_ps *data);
void		init_greedy_context(t_ps *data);
void		init_k_sort_context(t_ps *data);
void		init_radix_context(t_ps *data);

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

#endif