/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	verify_stack_is_sorted(t_ps *data)
{
	int	current_index;
	int	next_index;
	int	size;
	int	i;

	if (!data || data->b.element_count > 0)
		return (false);
	size = get_current_stack_size(&data->a);
	if (size <= 1)
		return (true);
	current_index = data->a.top;
	i = 0;
	while (i < size - 1)
	{
		next_index = calculate_next_down_index(&data->a, current_index);
		if (data->a.stack[current_index] > data->a.stack[next_index])
			return (false);
		current_index = next_index;
		i++;
	}
	return (true);
}

bool	validate_numeric_argument(char *arg)
{
	int		i;
	long	num;

	i = 0;
	if (!arg || !arg[0])
		return (false);
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!arg[i])
		return (false);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (false);
		i++;
	}
	num = ft_atol(arg);
	if (num > INT_MAX || num < INT_MIN)
		return (false);
	return (true);
}

bool	detect_duplicates_optimized(t_ps *data, int *numbers, int size)
{
    (void)data;
	if (size <= 1)
		return (false);
	if (size > HASH_TABLE_THRESHOLD)
		return (detect_duplicates_with_sorting(numbers, size));
	else
		return (detect_duplicates_with_sorting(numbers, size));
}
