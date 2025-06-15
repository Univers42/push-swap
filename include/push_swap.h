/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:55:45 by ugerkens          #+#    #+#             */
/*   Updated: 2025/06/15 22:57:35 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "stack_core.h"
# include "stack_operations.h"
# include "stack_utils.h"
# include "algorithms.h"
# include "optimizations.h"
# include "libft.h"

typedef struct s_queue	t_queue;
typedef struct s_vector	t_vector;

# define MODE_ALGORITHM_MASK	0x0F
# define MODE_DEBUG_MASK		0xF0

# define MODE_CHUNK_ALGO		0x00
# define MODE_GREEDY_ALGO		0x01
# define MODE_ALTERNATIVE_ALGO	0x02
# define MODE_HYBRID_ALGO		0x03
# define MODE_K_SORT_ALGO		0x04
# define MODE_QUEUE_ALGO		0x05
# define MODE_RADIX_ALGO		0x08
# define MODE_LIS_ALGO			0x0C

# define MODE_EVALUATION		0x00
# define MODE_STATS_DEBUG		0x10
# define MODE_VERBOSE_DEBUG		0x20
# define MODE_STEP_DEBUG		0x30
# define MODE_FULL_DEBUG		0x40

# define MODE_DEFAULT			0x00
# define MODE_GREEDY_STATS		0x11
# define MODE_GREEDY_VERBOSE	0x21
# define MODE_CHUNK_VERBOSE		0x20

bool		is_algorithm_mode(int mode, int algo);
bool		is_debug_level_mode(int mode, int lvl);
bool		has_debug_mode(int mode);
bool		has_stats_mode(int mode);
bool		has_verbose_mode(int mode);

void		debug_print_stack_state(t_ps *data, const char *context);
const char	*get_debug_level_name(int mode);
t_op		neutral_op(t_op op);

// Main utilities
void		print_algorithm_name(int mode);
void		execute_selected_algorithm(t_ps *data, int mode);
void		print_results(t_ps *data, int mode);

int			main(int argc, char *argv[]);

#endif
