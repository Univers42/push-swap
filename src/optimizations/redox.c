/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redox.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:58:15 by ugerkens          #+#    #+#             */
/*   Updated: 2025/07/08 14:55:25 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

void	redox(t_ps *data, t_chunk *max)
{
	t_stack	*a;

	a = &data->a;
	if (max->loc == TOP_A && max->size == 3
		&& is_consecutive(get_stack_element_at_position(a, 1),
			get_stack_element_at_position(a, 2),
			get_stack_element_at_position(a, 3),
			get_stack_element_at_position(a, 4))
		&& a_partly_sort(data, 4))
	{
		sort_three(data, max);
		return ;
	}
	if (max->loc == TOP_A
		&& get_stack_element_at_position(a, 1)
		== get_stack_element_at_position(a, 3) - 1
		&& a_partly_sort(data, 3))
	{
		sa(data);
		max->size--;
	}
	if (max->loc == TOP_A && a_partly_sort(data, 1))
		max->size--;
}

bool	a_partly_sort(t_ps *data, int from)
{
	int		i;
	t_stack	*a;
	int		value_current;

	a = &data->a;
	i = a->top;
	while (--from)
		i = calculate_next_down_index(a, i);
	while (a->stack[i] != data->a.capacity)
	{
		value_current = a->stack[i];
		i = calculate_next_down_index(a, i);
		if (a->stack[i] != value_current + 1)
			return (false);
	}
	return (true);
}

bool	is_consecutive(int a, int b, int c, int d)
{
	ft_swap(&a, &b, sizeof(int));
	ft_swap(&b, &c, sizeof(int));
	return ((b - a == 1) && (c - b == 1) && (d - c == 1));
}
