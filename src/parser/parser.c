/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syzygy <syzygy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/19 15:19:58 by syzygy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	is_stack_sorted(t_ps *data)
{
	int	current_index;
	int	next_index;
	int	size;
	int	i;

	if (!data || data->b.element_count > 0)
		return (false);
	size = get_stack_size(&data->a);
	if (size <= 1)
		return (true);
	current_index = data->a.top;
	i = 0;
	while (i < size - 1)
	{
		next_index = move_down(&data->a, current_index);
		if (data->a.stack[current_index] > data->a.stack[next_index])
			return (false);
		current_index = next_index;
		i++;
	}
	return (true);
}

bool	validate_numeric_argument(char *op)
{
	int		i;
	long	num;

	i = 0;
	if (!op || !op[0])
		return (false);
	if (op[i] == '-' || op[i] == '+')
		i++;
	if (!op[i])
		return (false);
	while (op[i])
	{
		if (!ft_isdigit(op[i]))
			return (false);
		i++;
	}
	num = ft_atol(op);
	if (num > INT_MAX || num < INT_MIN)
		return (false);
	return (true);
}
