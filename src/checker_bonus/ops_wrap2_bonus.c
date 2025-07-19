/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_wrap2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:30:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/19 02:42:56 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

void checker_rb(t_ps *data)
{
	checker_rotate(&data->b);
}

void checker_rr(t_ps *data)
{
	checker_rotate(&data->a);
	checker_rotate(&data->b);
}

void checker_rra(t_ps *data)
{
	checker_r_rotate(&data->a);
}

void checker_rrb(t_ps *data)
{
	checker_r_rotate(&data->b);
}

void checker_rrr(t_ps *data)
{
	checker_r_rotate(&data->a);
	checker_r_rotate(&data->b);
}
