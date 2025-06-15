/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alternative_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:31:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 19:06:53 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	alternative_sort(t_ps *data)
{
	ft_printf("🔄 Alternative sorting algorithm starting...\n");
	ft_printf("📊 Initial operations: %d\n", data->op_count);
	k_sort(data);
	ft_printf("📊 Operations after K-based sort: %d\n", data->op_count);
	ft_printf("🔄 K-based algorithm completed\n");
}
