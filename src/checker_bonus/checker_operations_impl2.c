/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_operations_impl2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 01:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 23:11:05 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

void	checker_ss(t_ps *data)
{
	checker_swap(&data->a);
	checker_swap(&data->b);
}

void	checker_ra(t_ps *data)
{
	checker_rotate(&data->a);
}

void	checker_rb(t_ps *data)
{
	checker_rotate(&data->b);
}

void	checker_rr(t_ps *data)
{
	checker_rotate(&data->a);
	checker_rotate(&data->b);
}
