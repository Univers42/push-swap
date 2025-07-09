/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remops.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:16:09 by codespace         #+#    #+#             */
/*   Updated: 2025/07/08 21:36:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	remove_op_from_list(t_list **list, t_list *to_remove)
{
	t_list	*current;
	t_list	*prev;

	if (!list || !*list || !to_remove)
		return ;
	current = *list;
	prev = NULL;
	while (current && current != to_remove)
	{
		prev = current;
		current = current->next;
	}
	if (!current)
		return ;
	if (prev)
		prev->next = current->next;
	else
		*list = current->next;
	free(current);
}

void	remove_op(t_list *to_delete)
{
	to_delete->prev->next = to_delete->next;
	if (to_delete->next)
		to_delete->next->prev = to_delete->prev;
	ft_lstdelone(to_delete, NULL);
}

void	process_elimination(t_ps *data, t_list *ref, t_list *cmp)
{
	remove_op_from_list(&data->op_list, ref);
	remove_op_from_list(&data->op_list, cmp);
}

t_list	*process_neutral_elimination(t_ps *data, t_list *ref)
{
	t_list	*cmp;
	t_op	op_neutral;
	t_op	ref_op;

	ref_op = op_from(ref);
	if (ref_op <= OP_NULL || ref_op >= 12)
		return (ref->next);
	op_neutral = neutral_op(ref_op);
	if (op_neutral != OP_NULL)
	{
		cmp = ref->next;
		while (cmp && !op_on_same_stack(ref_op, op_from(cmp))
			&& op_from(cmp) != op_neutral)
			cmp = cmp->next;
		if (cmp && op_from(cmp) == op_neutral)
		{
			process_elimination(data, ref, cmp);
			return (data->op_list);
		}
	}
	return (ref->next);
}

void	eliminate_neutral_op(t_ps *data)
{
	t_list	*ref;

	if (!data || !data->op_list)
		return ;
	ref = data->op_list;
	while (ref && ref->next)
	{
		ref = process_neutral_elimination(data, ref);
		if (!ref)
			break ;
	}
}
