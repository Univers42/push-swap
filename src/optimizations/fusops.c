/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fusops.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 23:50:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/09 17:42:21 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "tracker.h"

#include <stdint.h>

static t_op		child_op(t_op first, t_op second);
static t_list	*process_merge_operation(t_ps *data, t_list *reader);

void	merge_op(t_ps *data)
{
	t_list	*reader;

	if (!data || !data->op_list)
		return ;
	reader = data->op_list;
	while (reader && reader->next)
	{
		reader = process_merge_operation(data, reader);
		if (!reader)
			break ;
	}
}

static t_list	*process_merge_operation(t_ps *data, t_list *reader)
{
	t_op	child;
	t_op	first_op;
	t_op	second_op;

	first_op = op_from(reader);
	second_op = op_from(reader->next);
	if (first_op <= OP_NULL || first_op >= 12
		|| second_op <= OP_NULL || second_op >= 12)
		return (reader->next);
	child = child_op(first_op, second_op);
	if (child != OP_NULL)
	{
		reader->content = (void *)(uintptr_t)child;
		remove_op_from_list(&data->op_list, reader->next);
		return (reader);
	}
	return (reader->next);
}

static t_op	child_op(t_op first, t_op second)
{
	if (first <= OP_NULL || first >= 12 || second <= OP_NULL || second >= 12)
		return (OP_NULL);
	if ((first == OP_RA && second == OP_RB)
		|| (first == OP_RB && second == OP_RA))
		return (OP_RR);
	if ((first == OP_RRA && second == OP_RRB)
		|| (first == OP_RRB && second == OP_RRA))
		return (OP_RRR);
	if ((first == OP_SA && second == OP_SB)
		|| (first == OP_SB && second == OP_SA))
		return (OP_SS);
	return (OP_NULL);
}

void	post_sort_optimization(t_ps *data)
{
	if (!data || !data->op_list)
		return ;
	eliminate_neutral_op(data);
	merge_op(data);
	data->op_count = ft_lstsize(data->op_list);
}
