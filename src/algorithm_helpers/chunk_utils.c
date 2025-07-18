/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:58:02 by ugerkens          #+#    #+#             */
/*   Updated: 2025/07/18 16:04:48 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

int	chunk_value(t_ps *data, t_chunk *chunk, int n)
{
	t_loc	loc;
	t_stack	*stk;
	int		i;

	loc = chunk->loc;
	stk = loc_to_stack(data, loc);
	i = 0;
	if (loc == TOP_A || loc == TOP_B)
		i = stk->top;
	else if (loc == BOTTOM_A || loc == BOTTOM_B)
		i = stk->bottom;
	if (loc == TOP_A || loc == TOP_B)
		while (--n > 0)
			i = move_down(stk, i);
	else if (loc == BOTTOM_A || loc == BOTTOM_B)
		while (--n > 0)
			i = move_up(stk, i);
	return (stk->stack[i]);
}

int	chunk_max_value(t_ps *data, t_chunk *chunk)
{
	t_stack	*stk;
	int		size;
	int		max_value;
	int		i;

	stk = loc_to_stack(data, chunk->loc);
	size = chunk->size;
	max_value = 0;
	i = 0;
	if (chunk->loc == TOP_A || chunk->loc == TOP_B)
		i = stk->top;
	else if (chunk->loc == BOTTOM_A || chunk->loc == BOTTOM_B)
		i = stk->bottom;
	while (size--)
	{
		if (stk->stack[i] > max_value)
			max_value = stk->stack[i];
		if (chunk->loc == TOP_A || chunk->loc == TOP_B)
			i = move_down(stk, i);
		else if (chunk->loc == BOTTOM_A || chunk->loc == BOTTOM_B)
			i = move_up(stk, i);
	}
	return (max_value);
}

t_stack	*loc_to_stack(t_ps *data, t_loc loc)
{
	if (loc == TOP_A || loc == BOTTOM_A)
		return (&data->a);
	else
		return (&data->b);
}
