/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:15:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/19 02:51:16 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_op_info *get_op_info_table(void)
{
	static t_op_info table[12];
	static int initialized = 0;
	if (!initialized)
	{
		table[OP_NULL] = (t_op_info){ OP_NULL, STACK_NONE };
		table[OP_PA]   = (t_op_info){ OP_PB,   STACK_BOTH };
		table[OP_PB]   = (t_op_info){ OP_PA,   STACK_BOTH };
		table[OP_RA]   = (t_op_info){ OP_RRA,  STACK_A };
		table[OP_RB]   = (t_op_info){ OP_RRB,  STACK_B };
		table[OP_RRA]  = (t_op_info){ OP_RA,   STACK_A };
		table[OP_RRB]  = (t_op_info){ OP_RB,   STACK_B };
		table[OP_SA]   = (t_op_info){ OP_SA,   STACK_A };
		table[OP_SB]   = (t_op_info){ OP_SB,   STACK_B };
		table[OP_RR]   = (t_op_info){ OP_RRR,  STACK_BOTH };
		table[OP_RRR]  = (t_op_info){ OP_RR,   STACK_BOTH };
		initialized = 1;
	}
	return table;
}

t_op neutral_op(t_op op)
{
	t_op_info *table = get_op_info_table();
	if (op <= OP_NULL || op >= 12)
		return OP_NULL;
	return table[op].neutral;
}

bool op_on_same_stack(t_op ref, t_op to_check)
{
	t_op_info *table = get_op_info_table();
	if (ref <= OP_NULL || ref >= 12 || to_check <= OP_NULL || to_check >= 12)
		return false;
	return (table[ref].mask & table[to_check].mask) != 0;
}
