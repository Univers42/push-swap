/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_wrap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syzygy <syzygy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 01:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/19 15:46:54 by syzygy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

//wrapper using the mask rotate to redirect to op pb
void	checker_pb(t_ps *data)
{
	checker_push(&data->a, &data->b);
}

//wrapper using the mask rotate to redirect to op sa
void	checker_sa(t_ps *data)
{
	checker_swap(&data->a);
}

//wrapper using the mask rotate to redirect to op sb
void	checker_sb(t_ps *data)
{
	checker_swap(&data->b);
}

//wrapper using the mask rotate to redirect to op ss
void	checker_ss(t_ps *data)
{
	checker_swap(&data->a);
	checker_swap(&data->b);
}

//wrapper using the mask rotate to redirect to op ra
void	checker_ra(t_ps *data)
{
	checker_rotate(&data->a);
}
