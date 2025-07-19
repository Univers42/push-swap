/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syzygy <syzygy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:27:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/19 14:21:28 by syzygy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "checker_bonus.h"

bool	is_stack_sorted(t_ps *data)
{
	int	current_index;
	int	expected_rank;
	int	stack_size;

	if (data->a.element_count != data->a.capacity)
		return (false);
	stack_size = data->a.capacity;
	current_index = data->a.top;
	expected_rank = 1;
	while (expected_rank <= stack_size)
	{
		if (data->a.stack[current_index] != expected_rank)
			return (false);
		expected_rank++;
		current_index = move_down(&data->a, current_index);
	}
	return (true);
}

bool	validate_numeric_argument(char *arg)
{
	long long	num;
	int			sign;

	sign = 1;
	if (*arg == '\0')
		return (false);
	if (*arg == '-' || *arg == '+')
	{
		if (*arg == '-')
			sign = -1;
		arg++;
		if (*arg == '\0')
			return (false);
	}
	num = 0;
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (false);
		num = num * 10 + (*arg - '0');
		if ((sign == 1 && num > INT_MAX) || (sign == -1 && (-num < INT_MIN)))
			return (false);
		arg++;
	}
	return (true);
}
