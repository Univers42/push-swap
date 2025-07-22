/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 01:47:52 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/22 01:47:54 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "checker_bonus.h"

/**
 * Check if stack A is sorted in ascending order and stack B is empty
 * In our simple array implementation, elements are stored from index 0
 */
bool	is_stack_sorted(t_ps *data)
{
	int	i;

	if (!data || !data->a.stack)
		return (false);
	if (data->b.element_count > 0)
		return (false);
	if (data->a.element_count <= 1)
		return (true);
	i = 0;
	while (i < data->a.element_count - 1)
	{
		if (data->a.stack[i] > data->a.stack[i + 1])
			return (false);
		i++;
	}
	return (true);
}

/**
 * inspired by atoi logic, we use just a checker to 
 * be sure that the numbers are truly numbers but also
 * with a bound checking to avoid to be out of bound
 * as it is expected from the evaluation
 * @param arg string
 */
bool	validate_numeric_argument(char *op)
{
	long long	num;
	int			sign;

	sign = 1;
	if (*op == '\0')
		return (false);
	if (*op == '-' || *op == '+')
	{
		if (*op == '-')
			sign = -1;
		op++;
		if (*op == '\0')
			return (false);
	}
	num = 0;
	while (*op)
	{
		if (!ft_isdigit(*op))
			return (false);
		num = num * 10 + (*op - '0');
		if ((sign == 1 && num > INT_MAX) || (sign == -1 && (-num < INT_MIN)))
			return (false);
		op++;
	}
	return (true);
}
