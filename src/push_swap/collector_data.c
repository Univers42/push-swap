/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:09:02 by ugerkens          #+#    #+#             */
/*   Updated: 2025/06/15 14:52:59 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include <stdint.h>

void	save_op(t_ps *data, t_op op)
{
	t_list	*new;

	new = ft_lstnew((void *)(uintptr_t)op);
	if (!new)
		cleanup_and_exit_with_error(data);
	ft_lstadd_back(&data->op_list, new);
	increment_op_count(data);
}

void	increment_op_count(t_ps *data)
{
	data->op_count++;
	if (data->op_count >= data->op_capacity)
		data->op_capacity *= 2;
}


void	print_operations(t_list *head)
{
	t_list		*reader;
	const char	*op_str;

	reader = head;
	while (reader)
	{
		op_str = op_to_string(op_from(reader));
		if (op_str && op_str[0] != 'n')
			ft_printf("%s\n", op_str);
		reader = reader->next;
	}
}
