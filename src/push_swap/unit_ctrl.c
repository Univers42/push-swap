/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_ctrl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/18 15:37:43 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

void	config_chunk(t_ps *data)
{
	config_mask(data, chunk_sort, init_chunk_context, "Chunk Sort");
}

void config_greedy(t_ps *data) {
    config_mask(data, greedy_sort, init_greedy_context, "Greedy Sort");
}

/**
 * The jump table that hold all the alorith redirections..
 *  this is also here you might want to extend your own algorithm
 * A littl bit of bitwise operation to accelerate the cojnfiguration
 * verification
 * we apply a mask 0x7 = 0000 0111 in binary
 * The bitwise `AND` operation with  `0x7` keeps only the lowest 3 
 * bits of type.
 * this means `type` will always be a value between `0` and `7`
 * regardless of its original value
 * This ensur that only valid algorithkm indices (0-7) are used
 * indices are used in  Enum type
 * 
 * why do we do that to verify if the indices ijs ouut of bounds
 * or not..
 * if the branch is not correct we branch to the default value
 * 
 * This is a safe way to configure a dispatch algorithm based on
 * Enum or integer value
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
