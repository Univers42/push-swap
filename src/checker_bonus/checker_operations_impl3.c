/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_operations_impl3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:30:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 23:11:05 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

void	checker_rra(t_ps *data)
{
	checker_r_rotate(&data->a);
}

void	checker_rrb(t_ps *data)
{
	checker_r_rotate(&data->b);
}

void	checker_rrr(t_ps *data)
{
	checker_r_rotate(&data->a);
	checker_r_rotate(&data->b);
}
