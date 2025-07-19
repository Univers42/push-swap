/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strop_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syzygy <syzygy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 01:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/19 15:53:54 by syzygy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

/**
 * convert the op strings like `pa`, `rb`...
 * to its corresponding operation code `t_op` enum value.
 * it loop through the opeations table `op_table` which maps operation
 * names to codes.
 * For each entry, it compares the input string to the operation name
 * if it finds a match, it returns the corresponding operation code.
 * if not match is found, it returns `OP_NULL`
 */
t_op	tr_ops_code(const char *str)
{
	t_op_exec	*op_table;
	int			i;

	i = -1;
	op_table = get_op_table();
	if (!str || !*str)
		return (OP_NULL);
	while (++i < 12)
	{
		if (op_table[i].name && ft_strcmp(str, op_table[i].name) == 0)
			return ((t_op)i);
	}
	return (OP_NULL);
}
