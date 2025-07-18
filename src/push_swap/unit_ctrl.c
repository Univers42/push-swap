/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_ctrl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/18 15:12:51 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

/**
 * 
 */
static void	config_chunk(t_ps *data)
{
	data->algo.sort_fn = chunk_sort;
	data->algo.init_fn = init_chunk_context;
	data->algo.name = "Chunk Sort";
	init_chunk_context(data);
}

/**
 * The jump table that hold all the alorith redirections..
 *  this is also here you might want to extend your own algorithm
 */
void	select_algorithm(t_ps *data, t_algo_type type)
{
	static const t_config_fn	configurators[] = {
	[ALGO_CHUNK] = config_chunk,
	[ALGO_GREEDY] = config_greedy,
	[ALGO_K_SORT] = config_k_sort,
	[ALGO_RADIX] = config_radix,
	[ALGO_LIS] = config_lis,
	[ALGO_QUEUE] = config_queue
	};

	type = type & 0x7;
	if (type < 6 && configurators[type])
		configurators[type](data);
	else
		config_chunk(data);
}

//wrapper that dispatch the algos...
void	execute_algorithm(t_ps *data)
{
	if (data->algo.sort_fn)
		data->algo.sort_fn(data);
}
