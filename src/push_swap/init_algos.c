/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_algos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:28:58 by codespace         #+#    #+#             */
/*   Updated: 2025/07/18 15:50:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithms.h"
#include "push_swap.h"

/**
 * we initalize the context of algorithms... seperating the most possibly
 * the converns
 * - Prevents undefined behavoior
 * by setting all fields to know values (0,NULL), we avoid usign uninitialized
 * memory, which can cause unpredictable bugs or crashes
 * - algorithm readiness
 * Each sortin algorithm may need itw own data (chunk info,  node lists, counters)
 * to operate correctly. Initialization ensures the algorithm starts with a clean.
 * - Reset states between runs
 * if we run multiple sorts algos, initiliazing can be used as resets 
 * suppose we don't  that the memory will continue to iteratet to prohibitted
 * areas causing segmentation fault 
 * - Facilitates debugging
 * Known  initialj make is easier to track down issues, as we can distinguish
 * between uninitizalized and intentionally set data.
 * help avoiding segmentation fault error
 * - Consistency
 * all algorithms expect  their context to be set up in a certain way.
 * Centralized initlizatin guarantees this consistency
 * 
 */

void	init_chunk_context(t_ps *data)
{
	data->algo_ctx.u_ctx.s_chunk.current_chunk.loc = TOP_A;
	data->algo_ctx.u_ctx.s_chunk.current_chunk.size = data->total_size;
}

void	init_greedy_context(t_ps *data)
{
	data->algo_ctx.u_ctx.s_greedy.nodes = NULL;
	data->algo_ctx.u_ctx.s_greedy.nodes_count = 0;
	data->algo_ctx.u_ctx.s_greedy.phase = 0;
}

void	init_k_sort_context(t_ps *data)
{
	data->algo_ctx.u_ctx.s_k_sort.k_value = 0;
	data->algo_ctx.u_ctx.s_k_sort.range = 0;
}

void	init_radix_context(t_ps *data)
{
	data->algo_ctx.u_ctx.s_radix.bit_count = 0;
	data->algo_ctx.u_ctx.s_radix.max_bits = 0;
}
