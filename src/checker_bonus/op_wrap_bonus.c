/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_wrap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 01:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/19 02:43:55 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

void checker_pb(t_ps *data)
{
	checker_push(&data->a, &data->b);
}
void checker_sa(t_ps *data)
{
	checker_swap(&data->a);
}

void checker_sb(t_ps *data)
{
	checker_swap(&data->b);
}

void checker_ss(t_ps *data)
{
	checker_swap(&data->a);
	checker_swap(&data->b);
}

void checker_ra(t_ps *data)
{
	checker_rotate(&data->a);
}