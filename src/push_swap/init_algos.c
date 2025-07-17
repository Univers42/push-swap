/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_algos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:28:58 by codespace         #+#    #+#             */
/*   Updated: 2025/07/17 01:39:38 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithms.h"
#include "push_swap.h"

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
