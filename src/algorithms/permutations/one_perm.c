/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_perm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:32:28 by codespace         #+#    #+#             */
/*   Updated: 2025/07/09 22:31:14 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithms.h"
#include "push_swap.h"

void	sort_one(t_ps *data, t_chunk *to_sort)
{
	if (to_sort->loc == BOTTOM_A || to_sort->loc == BOTTOM_B
		|| to_sort->loc == TOP_B)
		move_from_to(data, to_sort->loc, TOP_A);
	to_sort->size -= 1;
}
