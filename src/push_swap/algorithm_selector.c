/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_selector.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	init_chunk_context(t_ps *data);
static void	init_greedy_context(t_ps *data);
static void	init_k_sort_context(t_ps *data);
static void	init_radix_context(t_ps *data);

void	select_algorithm(t_ps *data, t_algo_type type)
{
	data->algo.type = type;
	
	if (type == ALGO_CHUNK)
	{
		data->algo.sort_fn = chunk_sort;
		data->algo.name = "Chunk Sort";
		init_chunk_context(data);
	}
	else if (type == ALGO_GREEDY)
	{
		data->algo.sort_fn = greedy_sort;
		data->algo.name = "Greedy Sort";
		init_greedy_context(data);
	}
	else if (type == ALGO_K_SORT)
	{
		data->algo.sort_fn = k_sort;
		data->algo.name = "K-Sort";
		init_k_sort_context(data);
	}
	else if (type == ALGO_RADIX)
	{
		data->algo.sort_fn = radix_sort;
		data->algo.name = "Radix Sort";
		init_radix_context(data);
	}
	else if (type == ALGO_LIS)
	{
		data->algo.sort_fn = lis_sort;
		data->algo.name = "LIS Sort";
	}
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
	data->algo.ctx.radix.max_bits = calculate_max_bits_for_size(data->total_size);
	data->algo.ctx.radix.current_bit = 0;
}
