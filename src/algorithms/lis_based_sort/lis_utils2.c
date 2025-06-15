/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:20:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 16:00:57 by dlesieur         ###   ########.fr       */
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
	if (verify_stack_is_sorted(data))
		ft_printf("🔍 [LIS DEBUG] Final rotation successful!\n");
	else
		ft_printf("🔍 [LIS DEBUG] Final rotation incomplete\n");
}
