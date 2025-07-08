/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 23:20:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/08 18:36:56 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include <stdint.h>

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

t_op	op_from(t_list *node)
{
	if (!node)
		return (OP_NULL);
	return ((t_op)(uintptr_t)node->content);
}
