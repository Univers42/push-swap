/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:08:41 by ugerkens          #+#    #+#             */
/*   Updated: 2025/07/18 16:10:12 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "stack.h"

static void	push(t_stack *src, t_stack *dest);

void	pa(t_ps *data)
{
	push(&data->b, &data->a);
	save_op(data, OP_PA);
}

void	pb(t_ps *data)
{
	push(&data->a, &data->b);
	save_op(data, OP_PB);
}

static void	push(t_stack *src, t_stack *dest)
{
	int	new_dest_top;
	int	new_src_top;

	if (get_stack_size(dest) == dest->capacity
		|| get_stack_size(src) == 0)
		return ;
	new_dest_top = move_up(dest, dest->top);
	new_src_top = move_down(src, src->top);
	dest->stack[new_dest_top] = src->stack[src->top];
	dest->top = new_dest_top;
	dest->element_count++;
	src->stack[src->top] = 0;
	src->top = new_src_top;
	src->element_count--;
	if (dest->element_count == 1)
		dest->bottom = new_dest_top;
}
