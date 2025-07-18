/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:58:15 by ugerkens          #+#    #+#             */
/*   Updated: 2025/07/19 01:14:38 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

void	adjust_chunk(t_ps *data, t_chunk *max)
{
	t_stack	*a;

	a = &data->a;
	if (max->loc == TOP_A && max->size == 3
		&& is_consecutive(get_items(a, 1),
			get_items(a, 2),
			get_items(a, 3),
			get_items(a, 4))
		&& is_seg_sorted(data, 4))
	{
		sort_three(data, max);
		return ;
	}
	if (max->loc == TOP_A
		&& get_items(a, 1)
		== get_items(a, 3) - 1
		&& is_seg_sorted(data, 3))
	{
		sa(data);
		max->size--;
	}
	if (max->loc == TOP_A && is_seg_sorted(data, 1))
		max->size--;
}

bool	is_seg_sorted(t_ps *data, int from)
{
	t_stack	*a;
	int		i;
	int		prev;

	a = &data->a;
	i = a->top;
	if (a->element_count == 0)
		return (false);
	while (--from)
		i = move_down(a, i);
	prev = a->stack[i];
	i = move_down(a, i);
	while (a->stack[i] != a->capacity)
	{
		if (a->stack[i] != prev + 1)
			return (false);
		prev = a->stack[i];
		i = move_down(a, i);
	}
	return (true);
}

bool	is_consecutive(int a, int b, int c, int d)
{
	return ((b - a == 1) && (c - b == 1) && (d - c == 1));
}
