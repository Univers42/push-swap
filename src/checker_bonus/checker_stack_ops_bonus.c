/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_stack_ops_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syzygy <syzygy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 23:15:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/19 15:39:07 by syzygy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

/**
 * moves the top element from `src` to `dest`
 * for instance from `stack_a` to `stack_b`based on `FIFO` system
 * Checks if `dest` is full `src` is empty, if so, does nothing
 * calculates new top positions for both stack
 * copies the top value from src to `dest`
 * updates the top and element count for both stacks
 * clears the value from `src`
 * if `dest` was empty before, sets its bottom to the new top.
 */
void	checker_push(t_stack *src, t_stack *dest)
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

/**
 * Swaps the top two elements of the stack.
 * - check if the stack has fewer than 2 elements : do nothing
 * - find the position of the second element
 * swap the top and second element usign my efficient function ft_swap()
 */
void	checker_swap(t_stack *stk)
{
	int	second_pos;

	if (get_stack_size(stk) < 2)
		return ;
	second_pos = move_down(stk, stk->top);
	ft_swap(&stk->stack[stk->top], &stk->stack[second_pos], sizeof(int));
}

/**
 * Rotates the stack upwards (top element becomes bottom)
 * - check if the stack has fewer than 2 elemente: do nothing
 * - calculate teh new position
 * - is the stack is full:
 * - moves the top pointer down, bottom pointer up
 * if not full
 * 	- moves the top element to the new bottom position
 * 	- celar the old top
 *	- updates bottom and top pointers
 * 
 */
void	checker_rotate(t_stack *stk)
{
	int	new_top;
	int	new_bottom;

	if (get_stack_size(stk) < 2)
		return ;
	new_top = move_down(stk, stk->top);
	if (get_stack_size(stk) == stk->capacity)
	{
		stk->bottom = stk->top;
		stk->top = new_top;
	}
	else
	{
		new_bottom = move_down(stk, stk->bottom);
		stk->stack[new_bottom] = stk->stack[stk->top];
		stk->stack[stk->top] = 0;
		stk->bottom = new_bottom;
		stk->top = new_top;
	}
}

/**
 * Rotate the stack downwrds (bottom element becomes top elem)
 * - checks if the stack has fewer than 2elements, if so
 * does nothing
 * calculates the new bottom position
 * if the stack if full:
 * 	- moves teh bottom pointer up, top pointer to the old bottom
 * if the stack is not full:
 * 	- moves teh bottom element to the new top position
 * clears the old bottom
 * updates top and bottom pointers
 */
void	checker_r_rotate(t_stack *stk)
{
	int	new_top;
	int	new_bottom;

	if (get_stack_size(stk) < 2)
		return ;
	new_bottom = move_up(stk, stk->bottom);
	if (get_stack_size(stk) == stk->capacity)
	{
		stk->top = stk->bottom;
		stk->bottom = new_bottom;
	}
	else
	{
		new_top = move_up(stk, stk->top);
		stk->stack[new_top] = stk->stack[stk->bottom];
		stk->stack[stk->bottom] = 0;
		stk->top = new_top;
		stk->bottom = new_bottom;
	}
}

void	checker_pa(t_ps *data)
{
	checker_push(&data->b, &data->a);
}
