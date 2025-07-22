/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remops.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 01:48:34 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/22 04:26:31 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @brief Remove a node from a singly-linked list.
 *
 * Analogy: Like removing a book from a stack of books by finding it and
 * reconnecting the books above and below it.
 *
 * Example:
 *   list = [A] -> [B] -> [C], to_remove = [B]
 *   After: list = [A] -> [C]
 */
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

/**
 * @brief Remove a node from a doubly-linked list.
 *
 * Analogy: Like unlinking a train car from both the previous and next cars.
 *
 * Example:
 *   ... <-> [A] <-> [B] <-> [C] <-> ...
 *   remove_op([B]) results in ... <-> [A] <-> [C] <-> ...
 */
void	remove_op(t_list *to_delete)
{
	to_delete->prev->next = to_delete->next;
	if (to_delete->next)
		to_delete->next->prev = to_delete->prev;
	ft_lstdelone(to_delete, NULL);
}

/**
 * @brief Remove two operations from the operation list.
 *
 * Used when two operations cancel each other out (neutralize).
 * Analogy: Like erasing two opposite moves from a chess log.
 *
 * Example:
 *   op_list = [ra] -> [rra] -> ...
 *   process_elimination(data, [ra], [rra]) removes both.
 */
void	process_elimination(t_ps *data, t_list *ref, t_list *cmp)
{
	remove_op_from_list(&data->op_list, ref);
	remove_op_from_list(&data->op_list, cmp);
}

/**
 * @brief Scan for and eliminate neutralizing operation pairs.
 *
 * Looks for a pair of operations where the second neutralizes the first,
 * and removes both. Returns the next node to continue scanning.
 *
 * Analogy: Like scanning a to-do list for tasks that cancel each other out.
 *
 * Example:
 *   [ra] -> [rra] -> ...  (both removed)
 */
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

/**
 * @brief Iteratively eliminate all neutral operation pairs in the list.
 *
 * Analogy: Like repeatedly cleaning up a list of instructions by removing
 * all pairs of "do" and "undo" actions.
 *
 * Example:
 *   [ra] -> [rra] -> [sa] -> [sa] -> ...  (becomes ...)
 */
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
