/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_perm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:14:38 by codespace         #+#    #+#             */
/*   Updated: 2025/07/08 14:17:54 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "algorithms.h"
# include "push_swap.h"

static void	easy_sort_second(t_ps *data, t_chunk *to_sort);
static void	handle_top_b(t_ps *data, t_chunk *to_sort);
static void	handle_bottom_a(t_ps *data, t_chunk *to_sort);
static void	handle_bottom_b(t_ps *data, t_chunk *to_sort);

void	easy_sort(t_ps *data, t_chunk *to_sort)
{
	while (to_sort->loc != TOP_A && to_sort->size)
	{
		if (get_stack_element_at_position(&data->a, 1)
			== chunk_value(data, to_sort, 1) + 1 && to_sort->size > 0)
			sort_one(data, to_sort);
		else if (get_stack_element_at_position(&data->a, 1)
			== chunk_value(data, to_sort, 2) + 1 && to_sort->size > 1)
			easy_sort_second(data, to_sort);
		else
			break ;
	}
}

static void	easy_sort_second(t_ps *data, t_chunk *to_sort)
{
	if (to_sort->loc == TOP_B)
		handle_top_b(data, to_sort);
	else if (to_sort->loc == BOTTOM_A)
		handle_bottom_a(data, to_sort);
	else if (to_sort->loc == BOTTOM_B)
		handle_bottom_b(data, to_sort);
	to_sort->size--;
}

static void	handle_top_b(t_ps *data, t_chunk *to_sort)
{
	sb(data);
	pa(data);
	if (get_stack_element_at_position(&data->b, 1)
		== get_stack_element_at_position(&data->a, 1) - 1)
	{
		pa(data);
		to_sort->size--;
	}
}

static void	handle_bottom_a(t_ps *data, t_chunk *to_sort)
{
	rra(data);
	rra(data);
	sa(data);
	if (get_stack_element_at_position(&data->a, 1)
		== get_stack_element_at_position(&data->a, 2) - 1)
		to_sort->size--;
	else
		ra(data);
}

static void	handle_bottom_b(t_ps *data, t_chunk *to_sort)
{
	rrb(data);
	rrb(data);
	pa(data);
	if (get_stack_element_at_position(&data->b, 1)
		== get_stack_element_at_position(&data->a, 1) - 1)
	{
		pa(data);
		to_sort->size--;
	}
	else
		rb(data);
}
