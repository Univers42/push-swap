/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:31:22 by codespace         #+#    #+#             */
/*   Updated: 2025/07/09 22:26:20 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
this function updates the location field (loc) of a t_chunk structure
(to_sort) ased on its current position and size in a push_swap stack.
if to_sort->loc is BOTTOM_B and the current size b equals to sort->size,
it set to_sort->loc to TOP_B and so on...

@note this is used to track if a chunk has been moved to the top oof
a stack,, based on its size and position
*/
void	chunk_to_the_top(t_ps *data, t_chunk *to_sort)
{
	if (to_sort->loc == BOTTOM_B
		&& get_current_stack_size(&data->b) == to_sort->size)
		to_sort->loc = TOP_B;
	if (to_sort->loc == BOTTOM_A
		&& get_current_stack_size(&data->a) == to_sort->size)
		to_sort->loc = TOP_A;
}
