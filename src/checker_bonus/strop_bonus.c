/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strop_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syzygy <syzygy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 01:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/19 14:35:24 by syzygy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

t_op	string_to_op(const char *str)
{
	t_op_exec	*op_table;
	int			i;

	i = 0;
	op_table = get_op_table();
	if (!str || !*str)
		return (OP_NULL);
	while (i < 12)
	{
		if (op_table[i].name && ft_strcmp(str, op_table[i].name) == 0)
			return ((t_op)i);
		i++;
	}
	return (OP_NULL);
}

void	error_read_op(t_ps *data, char *line)
{
	(void)data;
	if (line)
		free(line);
	ft_putendl_fd("Error", 2);
	exit(255);
}
