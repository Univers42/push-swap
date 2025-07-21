/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_algos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:28:58 by codespace         #+#    #+#             */
/*   Updated: 2025/07/21 21:13:14 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithms.h"
#include "push_swap.h"

void	config_mask(t_ps *data, void (*ctx_alg)(t_ps *),
					void (*init)(t_ps *), t_string name)
{
	data->algo.sort_fn = ctx_alg;
	data->algo.init_fn = init;
	data->algo.name = name;
	if (init)
		init(data);
}

void	config_k_sort(t_ps *data)
{
	config_mask(data, k_sort, init_k_sort_context, "K-Sort");
}

void	config_radix(t_ps *data)
{
	config_mask(data, radix_sort, init_radix_context, "Radix-Sort");
}

void	config_lis(t_ps *data)
{
	config_mask(data, lis_sort, NULL, "LIS-Sort");
}

void	config_queue(t_ps *data)
{
	config_mask(data, queue_sort, NULL, "Queue_Sort");
}
