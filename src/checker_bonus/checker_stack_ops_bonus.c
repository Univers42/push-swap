/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_stack_ops_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 01:47:26 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/22 01:47:27 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

/**
 * Push operation - moves the top element from src to dest
 * In a simple array implementation, top element is at index 0
 * We shift elements accordingly
 * 1) we shift all elemments in dest down by one position
 * 2) move top element from src to dest
 * 3) shift all elements in src up  by one position
 */
void	checker_push(t_stack *src, t_stack *dest)
{
	int	i;

	if (!src || !dest || !src->stack || !dest->stack)
		return ;
	if (src->element_count == 0 || dest->element_count >= dest->capacity)
		return ;
	i = dest->element_count;
	while (i > 0)
	{
		dest->stack[i] = dest->stack[(i) - 1];
		i--;
	}
	dest->stack[0] = src->stack[0];
	dest->element_count++;
	i = -1;
	while (++i < src->element_count - 1)
		src->stack[i] = src->stack[i + 1];
	src->element_count--;
}

/**
 * Swap the top two elements of the stack
 * Top two elements are at indices 0 and 1
 */
void	checker_swap(t_stack *stk)
{
	int	temp;

	if (!stk || !stk->stack || stk->element_count < 2)
		return ;
	temp = stk->stack[0];
	stk->stack[0] = stk->stack[1];
	stk->stack[1] = temp;
}

/**
 * Rotate up - top element becomes bottom
 * First element goes to the end, all others shift up
 */
void	checker_rotate(t_stack *stk)
{
	int	temp;
	int	i;

	if (!stk || !stk->stack || stk->element_count < 2)
		return ;
	temp = stk->stack[0];
	i = -1;
	while (++i < stk->element_count - 1)
		stk->stack[i] = stk->stack[i + 1];
	stk->stack[stk->element_count - 1] = temp;
}

/**
 * Reverse rotate - bottom element becomes top
 * Last element goes to the beginning, all others shift down
 */
void	checker_r_rotate(t_stack *stk)
{
	int	temp;
	int	i;

	if (!stk || !stk->stack || stk->element_count < 2)
		return ;
	temp = stk->stack[stk->element_count - 1];
	i = stk->element_count - 1;
	while (i > 0)
	{
		stk->stack[i] = stk->stack[i - 1];
		i--;
	}
	stk->stack[0] = temp;
}

void	checker_pa(t_ps *data)
{
	checker_push(&data->b, &data->a);
}
