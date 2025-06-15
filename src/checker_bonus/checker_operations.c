/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 01:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 23:13:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static void	execute_push_operations(t_ps *data, t_op operation);
static void	execute_swap_operations(t_ps *data, t_op operation);
static void	execute_rotate_operations(t_ps *data, t_op operation);
static void	execute_reverse_rotate_operations(t_ps *data, t_op operation);

void	execute_checker_operation(t_ps *data, t_op operation)
{
	if (operation == OP_PA || operation == OP_PB)
		execute_push_operations(data, operation);
	else if (operation == OP_SA || operation == OP_SB || operation == OP_SS)
		execute_swap_operations(data, operation);
	else if (operation == OP_RA || operation == OP_RB || operation == OP_RR)
		execute_rotate_operations(data, operation);
	else if (operation == OP_RRA || operation == OP_RRB || operation == OP_RRR)
		execute_reverse_rotate_operations(data, operation);
}

static void	execute_push_operations(t_ps *data, t_op operation)
{
	if (operation == OP_PA)
		checker_push(&data->b, &data->a);
	else if (operation == OP_PB)
		checker_push(&data->a, &data->b);
}

static void	execute_swap_operations(t_ps *data, t_op operation)
{
	if (operation == OP_SA)
		checker_swap(&data->a);
	else if (operation == OP_SB)
		checker_swap(&data->b);
	else if (operation == OP_SS)
	{
		checker_swap(&data->a);
		checker_swap(&data->b);
	}
}

static void	execute_rotate_operations(t_ps *data, t_op operation)
{
	if (operation == OP_RA)
		checker_rotate(&data->a);
	else if (operation == OP_RB)
		checker_rotate(&data->b);
	else if (operation == OP_RR)
	{
		checker_rotate(&data->a);
		checker_rotate(&data->b);
	}
}

static void	execute_reverse_rotate_operations(t_ps *data, t_op operation)
{
	if (operation == OP_RRA)
		checker_r_rotate(&data->a);
	else if (operation == OP_RRB)
		checker_r_rotate(&data->b);
	else if (operation == OP_RRR)
	{
		checker_r_rotate(&data->a);
		checker_r_rotate(&data->b);
	}
}
