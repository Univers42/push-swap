/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_algos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:28:58 by codespace         #+#    #+#             */
/*   Updated: 2025/07/08 21:35:03 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithms.h"
#include "push_swap.h"

void	config_greedy(t_ps *data)
{
	data->algo.sort_fn = greedy_sort;
	data->algo.init_fn = init_greedy_context;
	data->algo.name = "Greedy Sort";
	init_greedy_context(data);
}

void	config_k_sort(t_ps *data)
{
	data->algo.sort_fn = k_sort;
	data->algo.init_fn = init_k_sort_context;
	data->algo.name = "K-Sort";
	init_k_sort_context(data);
}

void	config_radix(t_ps *data)
{
	data->algo.sort_fn = radix_sort;
	data->algo.init_fn = init_radix_context;
	data->algo.name = "Radix Sort";
	init_radix_context(data);
}

void	config_lis(t_ps *data)
{
	data->algo.sort_fn = lis_sort;
	data->algo.init_fn = NULL;
	data->algo.name = "LIS Sort";
}

void	config_queue(t_ps *data)
{
	data->algo.sort_fn = queue_sort;
	data->algo.init_fn = NULL;
	data->algo.name = "Queue Sort";
}
