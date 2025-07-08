/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_ctrl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/08 21:21:52 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

static void	init_chunk_context(t_ps *data);
static void	init_greedy_context(t_ps *data);
static void	init_k_sort_context(t_ps *data);
static void	init_radix_context(t_ps *data);
static void	init_algo_table(t_algo_state *table);

void	select_algorithm(t_ps *data, t_algo_type type)
{
	static t_algo_state	algo_table[6];
	static int			initialized = 0;
	
	if (!initialized)
	{
		init_algo_table(algo_table);
		initialized = 1;
	}
	
	data->algo.type = type;
	type = type & 0x7;
	
	if (type < 6 && algo_table[type].sort_fn)
	{
		data->algo.sort_fn = algo_table[type].sort_fn;
		data->algo.init_fn = algo_table[type].init_fn;
		data->algo.name = algo_table[type].name;
		if (data->algo.init_fn)
			data->algo.init_fn(data);
	}
	else
	{
		data->algo.sort_fn = chunk_sort;
		data->algo.init_fn = init_chunk_context;
		data->algo.name = "Chunk Sort (Default)";
		init_chunk_context(data);
	}
}

static void	init_algo_table(t_algo_state *table)
{
	ft_memset(table, 0, sizeof(t_algo_state) * 6);
	
	table[ALGO_CHUNK].type = ALGO_CHUNK;
	table[ALGO_CHUNK].sort_fn = chunk_sort;
	table[ALGO_CHUNK].init_fn = init_chunk_context;
	table[ALGO_CHUNK].name = "Chunk Sort";
	
	table[ALGO_GREEDY].type = ALGO_GREEDY;
	table[ALGO_GREEDY].sort_fn = greedy_sort;
	table[ALGO_GREEDY].init_fn = init_greedy_context;
	table[ALGO_GREEDY].name = "Greedy Sort";
	
	table[ALGO_K_SORT].type = ALGO_K_SORT;
	table[ALGO_K_SORT].sort_fn = k_sort;
	table[ALGO_K_SORT].init_fn = init_k_sort_context;
	table[ALGO_K_SORT].name = "K-Sort";
	
	table[ALGO_RADIX].type = ALGO_RADIX;
	table[ALGO_RADIX].sort_fn = radix_sort;
	table[ALGO_RADIX].init_fn = init_radix_context;
	table[ALGO_RADIX].name = "Radix Sort";
	
	table[ALGO_LIS].type = ALGO_LIS;
	table[ALGO_LIS].sort_fn = lis_sort;
	table[ALGO_LIS].init_fn = NULL;
	table[ALGO_LIS].name = "LIS Sort";
	
	table[ALGO_QUEUE].type = ALGO_QUEUE;
	table[ALGO_QUEUE].sort_fn = queue_sort;
	table[ALGO_QUEUE].init_fn = NULL;
	table[ALGO_QUEUE].name = "Queue Sort";
}

void	execute_algorithm(t_ps *data)
{
	if (data->algo.sort_fn)
		data->algo.sort_fn(data);
}

static void	init_chunk_context(t_ps *data)
{
	data->algo.ctx.chunk.current_chunk.loc = TOP_A;
	data->algo.ctx.chunk.current_chunk.size = data->total_size;
}

static void	init_greedy_context(t_ps *data)
{
	data->algo.ctx.greedy.nodes = NULL;
	data->algo.ctx.greedy.nodes_count = 0;
	data->algo.ctx.greedy.phase = 0;
}

static void	init_k_sort_context(t_ps *data)
{
	data->algo.ctx.k_sort.k_value = ft_sqrt(data->total_size) * 14 / 10;
	data->algo.ctx.k_sort.range = data->algo.ctx.k_sort.k_value;
	data->algo.ctx.k_sort.i = 1;
	data->algo.ctx.k_sort.target_remaining = 3;
}

static void	init_radix_context(t_ps *data)
{
	int	size;

	size = data->total_size;
	data->algo.ctx.radix.max_bits = calculate_max_bits_for_size(size);
	data->algo.ctx.radix.current_bit = 0;
}
