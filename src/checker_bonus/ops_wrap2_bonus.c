/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_wrap2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syzygy <syzygy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:30:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/19 15:47:36 by syzygy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

//wrapper using the mask rotate to redirect to op rb
void	checker_rb(t_ps *data)
{
	checker_rotate(&data->b);
}

//wrapper using the mask rotate to redirect to op rr
void	checker_rr(t_ps *data)
{
	checker_rotate(&data->a);
	checker_rotate(&data->b);
}

//wrapper using the mask rotate to redirect to op rra
void	checker_rra(t_ps *data)
{
	checker_r_rotate(&data->a);
}

//wrapper using the mask rotate to redirect to op rrb
void	checker_rrb(t_ps *data)
{
	checker_r_rotate(&data->b);
}

//wrapper using the mask rotate to redirect to op rrr
void	checker_rrr(t_ps *data)
{
	checker_r_rotate(&data->a);
	checker_r_rotate(&data->b);
}
