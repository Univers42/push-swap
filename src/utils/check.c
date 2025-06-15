/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:45:52 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 14:46:38 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	check_if_stack_is_full(t_stack *stk)
{
	return (stk->element_count == stk->capacity);
}

bool	check_if_stack_is_empty(t_stack *stk)
{
	return (stk->element_count == 0);
}
