/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_perm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 07:28:06 by codespace         #+#    #+#             */
/*   Updated: 2025/07/17 07:31:26 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_three_simple(t_ps *data)
{
	int	first;
	int	second;
	int	third;

	if (get_current_stack_size(&data->a) != 3)
		return ;
	first = get_stack_element_at_position(&data->a, 1);
	second = get_stack_element_at_position(&data->a, 2);
	third = get_stack_element_at_position(&data->a, 3);
	if (first > second && second < third && first < third)
		sa(data);
	else if (first > second && second > third)
	{
		sa(data);
		rra(data);
	}
	else if (first > second && second < third && first > third)
		ra(data);
	else if (first < second && second > third && first < third)
	{
		sa(data);
		ra(data);
	}
	else if (first < second && second > third && first > third)
		rra(data);
}
