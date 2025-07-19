/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syzygy <syzygy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/19 15:07:31 by syzygy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

// Operation wrappers for t_ps *

static t_op_exec	op_mask(t_string name,
								void (*op_func)(t_ps *), int bit_mask)
{
	return ((t_op_exec)
		{
			.name = name,
			.op_func = op_func,
			.stack_mask = bit_mask
		});
}

static void	init_op_table(t_op_exec *table)
{
	table[OP_PA] = op_mask("pa", checker_pa, STACK_A_BIT);
	table[OP_PB] = op_mask("pb", checker_pb, STACK_A_BIT);
	table[OP_SA] = op_mask("sa", checker_sa, STACK_A_BIT);
	table[OP_SB] = op_mask("sb", checker_sb, STACK_B_BIT);
	table[OP_SS] = op_mask("ss", checker_ss,
			STACK_A_BIT | STACK_B_BIT | DUAL_OP_BIT);
	table[OP_RA] = op_mask("ra", checker_ra, STACK_A_BIT);
	table[OP_RB] = op_mask("rb", checker_rb, STACK_B_BIT);
	table[OP_RR] = op_mask("rr", checker_rr,
			STACK_A_BIT | STACK_B_BIT | DUAL_OP_BIT);
	table[OP_RRA] = op_mask("rra", checker_rra, STACK_A_BIT);
	table[OP_RRB] = op_mask("rrb", checker_rrb, STACK_B_BIT);
	table[OP_RRR] = op_mask("rrr", checker_rrr,
			STACK_A_BIT | STACK_B_BIT | DUAL_OP_BIT);
}

t_op_exec	*get_op_table(void)
{
	static t_op_exec	table[12];
	static int			lazy = 0;

	if (!lazy)
	{
		init_op_table(table);
		lazy = 1;
	}
	return (table);
}

/**
 * retrive the map of operations
 * checker if the operation code is out of bound
 * execute the operations of movement to sort the list
 */
void	run_op(t_ps *data, t_op operation)
{
	t_op_exec	*op_table;

	op_table = get_op_table();
	if (operation <= OP_NULL || operation >= 12)
		return ;
	if (op_table[operation].op_func)
		op_table[operation].op_func(data);
}
