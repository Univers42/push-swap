/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:15:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 15:12:02 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_op	neutral_op(t_op op)
{
	if (op <= OP_NULL || op >= 12)
		return (OP_NULL);
	if (op == OP_PA)
		return (OP_PB);
	if (op == OP_PB)
		return (OP_PA);
	if (op == OP_RA)
		return (OP_RRA);
	if (op == OP_RB)
		return (OP_RRB);
	if (op == OP_RRA)
		return (OP_RA);
	if (op == OP_RRB)
		return (OP_RB);
	if (op == OP_SA)
		return (OP_SA);
	if (op == OP_SB)
		return (OP_SB);
	if (op == OP_RR)
		return (OP_RRR);
	if (op == OP_RRR)
		return (OP_RR);
	return (OP_NULL);
}

bool	op_on_same_stack(t_op ref, t_op to_check)
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

void	remove_op(t_list *to_delete)
{
	to_delete->prev->next = to_delete->next;
	if (to_delete->next)
		to_delete->next->prev = to_delete->prev;
	ft_lstdelone(to_delete, NULL);
}
