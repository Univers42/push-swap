/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 01:46:35 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/22 01:46:36 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	lis_print_final_result(bool is_ascending)
{
	if (is_ascending)
		ft_printf("🔍 [LIS DEBUG] Elements are in ascending order!\n");
	else
		ft_printf("🔍 [LIS DEBUG] Elements are NOT in ascending order!\n");
}

void	lis_verify_final_rotation(t_ps *data)
{
	if (is_stack_sorted(data))
		ft_printf("🔍 [LIS DEBUG] Final rotation successful!\n");
	else
		ft_printf("🔍 [LIS DEBUG] Final rotation incomplete\n");
}
