/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 01:47:42 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/22 04:21:19 by dlesieur         ###   ########.fr       */
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

/**
 * @brief Initializes the operation table with operation names, function pointers, and bitmasks.
 *
 * The bitmask (stack_mask) is used to encode which stack(s) an operation affects and
 * whether it is a dual operation. This allows for efficient checks and flexible logic
 * elsewhere in the code (for example, to know if an operation is valid for a given stack,
 * or to apply optimizations for dual operations).
 *
 * Typical bitmask values:
 *   - STACK_A_BIT:   Operation affects stack A (e.g., "sa", "pa", "ra", "rra")
 *   - STACK_B_BIT:   Operation affects stack B (e.g., "sb", "pb", "rb", "rrb")
 *   - DUAL_OP_BIT:   Operation affects both stacks simultaneously (e.g., "ss", "rr", "rrr")
 *
 * Examples:
 *   - "sa" (swap A):      stack_mask = STACK_A_BIT
 *   - "sb" (swap B):      stack_mask = STACK_B_BIT
 *   - "ss" (swap both):   stack_mask = STACK_A_BIT | STACK_B_BIT | DUAL_OP_BIT
 *   - "pa" (push A):      stack_mask = STACK_A_BIT (since it pushes to A)
 *   - "pb" (push B):      stack_mask = STACK_A_BIT (since it pushes from A)
 *   - "ra" (rotate A):    stack_mask = STACK_A_BIT
 *   - "rr" (rotate both): stack_mask = STACK_A_BIT | STACK_B_BIT | DUAL_OP_BIT
 *
 * Usage:
 *   - The bitmask can be used to filter or identify operations by the stack(s) they affect.
 *   - For example, to check if an operation is a dual operation:
 *         if (stack_mask & DUAL_OP_BIT) { ... }
 *   - Or to check if it affects stack A:
 *         if (stack_mask & STACK_A_BIT) { ... }
 */
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
