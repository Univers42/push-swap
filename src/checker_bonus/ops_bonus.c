/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/08 21:01:45 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

#if VISUALIZE == 1
# include "visualizer.h"

// Add op_to_string for visualization
const char	*op_to_string(t_op op)
{
	static const char	*op_strings[] = {
	[OP_NULL] = "null_op",
	[OP_PA] = "pa",
	[OP_PB] = "pb",
	[OP_RA] = "ra",
	[OP_RB] = "rb",
	[OP_RR] = "rr",
	[OP_RRA] = "rra",
	[OP_RRB] = "rrb",
	[OP_RRR] = "rrr",
	[OP_SA] = "sa",
	[OP_SB] = "sb",
	[OP_SS] = "ss"
	};

	if (op < 0 || op >= (sizeof(op_strings) / sizeof(op_strings[0])))
		return ("invalid_op");
	return (op_strings[op]);
}
#endif

typedef struct s_op_exec
{
	void	(*single_op)(t_stack *);
	void	(*dual_op)(t_stack *, t_stack *);
	int		stack_mask;
	int		is_dual;
}	t_op_exec;

#define STACK_A_BIT 0x1
#define STACK_B_BIT 0x2
#define DUAL_OP_BIT 0x4

static void	init_op_table(t_op_exec *table)
{
	table[OP_PA] = (t_op_exec){NULL, checker_push, STACK_B_BIT, 1};
	table[OP_PB] = (t_op_exec){NULL, checker_push, STACK_A_BIT, 1};
	table[OP_SA] = (t_op_exec){checker_swap, NULL, STACK_A_BIT, 0};
	table[OP_SB] = (t_op_exec){checker_swap, NULL, STACK_B_BIT, 0};
	table[OP_SS] = (t_op_exec){checker_swap, NULL, STACK_A_BIT | STACK_B_BIT | DUAL_OP_BIT, 0};
	table[OP_RA] = (t_op_exec){checker_rotate, NULL, STACK_A_BIT, 0};
	table[OP_RB] = (t_op_exec){checker_rotate, NULL, STACK_B_BIT, 0};
	table[OP_RR] = (t_op_exec){checker_rotate, NULL, STACK_A_BIT | STACK_B_BIT | DUAL_OP_BIT, 0};
	table[OP_RRA] = (t_op_exec){checker_r_rotate, NULL, STACK_A_BIT, 0};
	table[OP_RRB] = (t_op_exec){checker_r_rotate, NULL, STACK_B_BIT, 0};
	table[OP_RRR] = (t_op_exec){checker_r_rotate, NULL, STACK_A_BIT | STACK_B_BIT | DUAL_OP_BIT, 0};
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
		return;
	
	op = &op_table[operation];
	
	if (op->is_dual)
	{
		t_stack *src = (op->stack_mask & STACK_A_BIT) ? &data->a : &data->b;
		t_stack *dst = (op->stack_mask & STACK_A_BIT) ? &data->b : &data->a;
		op->dual_op(src, dst);
	}
	else if (op->stack_mask & DUAL_OP_BIT)
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