/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/09 19:31:55 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static void	init_op_table(t_op_exec *table)
{
	table[OP_PA] = (t_op_exec){NULL, checker_push, STACK_B_BIT, 1};
	table[OP_PB] = (t_op_exec){NULL, checker_push, STACK_A_BIT, 1};
	table[OP_SA] = (t_op_exec){checker_swap, NULL, STACK_A_BIT, 0};
	table[OP_SB] = (t_op_exec){checker_swap, NULL, STACK_B_BIT, 0};
	table[OP_SS] = (t_op_exec){checker_swap, NULL, STACK_A_BIT | STACK_B_BIT
		| DUAL_OP_BIT, 0};
	table[OP_RA] = (t_op_exec){checker_rotate, NULL, STACK_A_BIT, 0};
	table[OP_RB] = (t_op_exec){checker_rotate, NULL, STACK_B_BIT, 0};
	table[OP_RR] = (t_op_exec){checker_rotate, NULL, STACK_A_BIT | STACK_B_BIT
		| DUAL_OP_BIT, 0};
	table[OP_RRA] = (t_op_exec){checker_r_rotate, NULL, STACK_A_BIT, 0};
	table[OP_RRB] = (t_op_exec){checker_r_rotate, NULL, STACK_B_BIT, 0};
	table[OP_RRR] = (t_op_exec){checker_r_rotate, NULL, STACK_A_BIT
		| STACK_B_BIT | DUAL_OP_BIT, 0};
}

static void	execute_dual_operation(t_ps *data, t_op_exec *op)
{
	t_stack	*src;
	t_stack	*dst;

	if (op->stack_mask & STACK_A_BIT)
	{
		src = &data->a;
		dst = &data->b;
	}
	else
	{
		src = &data->b;
		dst = &data->a;
	}
	op->dual_op(src, dst);
}

static void	execute_single_operation(t_ps *data, t_op_exec *op)
{
	if (op->stack_mask & DUAL_OP_BIT)
	{
		op->single_op(&data->a);
		op->single_op(&data->b);
	}
	else
	{
		if (op->stack_mask & STACK_A_BIT)
			op->single_op(&data->a);
		if (op->stack_mask & STACK_B_BIT)
			op->single_op(&data->b);
	}
}

void	execute_checker_operation(t_ps *data, t_op operation)
{
	static t_op_exec	op_table[12];
	static int			initialized = 0;
	t_op_exec			*op;

	if (!initialized)
	{
		init_op_table(op_table);
		initialized = 1;
	}
	if (operation <= OP_NULL || operation >= 12)
		return ;
	op = &op_table[operation];
	if (op->is_dual)
		execute_dual_operation(data, op);
	else
		execute_single_operation(data, op);
}
