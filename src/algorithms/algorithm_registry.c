/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_registry.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

// Define mode constants if they're not already defined
#ifndef MODE_GREEDY_ALGO
# define MODE_GREEDY_ALGO 1
# define MODE_K_SORT_ALGO 2
# define MODE_RADIX_ALGO 3
# define MODE_CHUNK_ALGO 4
#endif

// Helper function to check algorithm mode
static int is_algorithm_mode(int mode, int algo_flag)
{
    return (mode & algo_flag) != 0;
}

void	init_algorithm(t_ps *data, int mode)
{
	if (is_algorithm_mode(mode, MODE_GREEDY_ALGO))
	{
		data->algo.type = ALGO_GREEDY;
		data->algo.sort_fn = greedy_sort;
		data->algo.ctx.greedy.nodes = NULL;
		data->algo.ctx.greedy.nodes_count = 0;
	}
	else if (is_algorithm_mode(mode, MODE_K_SORT_ALGO))
	{
		data->algo.type = ALGO_K_SORT;
		data->algo.sort_fn = NULL; // k_sort not implemented yet
		data->algo.ctx.k_sort.k_value = 0;
		data->algo.ctx.k_sort.range = 0;
	}
	else if (is_algorithm_mode(mode, MODE_RADIX_ALGO))
	{
		data->algo.type = ALGO_RADIX;
		data->algo.sort_fn = radix_sort;
		data->algo.ctx.radix.max_bits = 0;
		data->algo.ctx.radix.current_bit = 0;
	}
	else  // Default to chunk
	{
		data->algo.type = ALGO_CHUNK;
		data->algo.sort_fn = chunk_sort;
		data->algo.ctx.chunk.chunk_size = 0;
		data->algo.ctx.chunk.n_chunks = 0;
	}
}

void	run_algorithm(t_ps *data)
{
	if (data->algo.sort_fn)
		data->algo.sort_fn(data);
}
