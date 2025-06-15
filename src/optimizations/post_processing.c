/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:58:19 by ugerkens          #+#    #+#             */
/*   Updated: 2025/06/15 15:12:22 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdint.h>

static bool		op_on_same_stack(t_op ref, t_op to_check);
static void		process_elimination(t_ps *data, t_list *ref, t_list *cmp);
static t_list	*process_neutral_elimination(t_ps *data, t_list *ref);

void	post_sort_optimization(t_ps *data)
{
	if (!data || !data->op_list)
		return ;
	eliminate_neutral_op(data);
	merge_op(data);
	data->op_count = ft_lstsize(data->op_list);
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

static t_list	*process_neutral_elimination(t_ps *data, t_list *ref)
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

static void	process_elimination(t_ps *data, t_list *ref, t_list *cmp)
{
	remove_op_from_list(&data->op_list, ref);
	remove_op_from_list(&data->op_list, cmp);
}

static bool	op_on_same_stack(t_op ref, t_op to_check)
{
	if (ref <= OP_NULL || ref >= 12 || to_check <= OP_NULL || to_check >= 12)
		return (false);
	if (ref == OP_PA || ref == OP_PB || ref == OP_RR || ref == OP_RRR)
		return (true);
	if (to_check == OP_PA || to_check == OP_PB || to_check == OP_RR
		|| to_check == OP_RRR)
		return (true);
	if (ref == OP_RA || ref == OP_RRA || ref == OP_SA)
		return (to_check == OP_RA || to_check == OP_RRA || to_check == OP_SA);
	if (ref == OP_RB || ref == OP_RRB || ref == OP_SB)
		return (to_check == OP_RB || to_check == OP_RRB || to_check == OP_SB);
	return (false);
}
