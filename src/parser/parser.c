/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 01:48:44 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/22 04:34:23 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @brief Checks if stack A is sorted in ascending order and stack B is empty.
 *
 * This function verifies that the stack 'a' is sorted from top to bottom
 * (using circular buffer logic), and that stack 'b' is empty.
 *
 * Example:
 *   A = [1, 2, 3, 4], B = []  => returns true
 *   A = [3, 2, 1], B = []     => returns false
 *   A = [1, 2, 3], B = [4]    => returns false
 *
 * Importance: Used to determine if the sorting is complete and correct.
 */
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

/**
 * @brief Validates that a string represents a valid integer argument.
 *
 * Checks that the string is a valid integer (optionally signed),
 * contains only digits,
 * and is within the bounds of INT_MIN and INT_MAX.
 *
 * Example:
 *   "42"      => true
 *   "-123"    => true
 *   "2147483648" => false (out of bounds)
 *   "abc"     => false
 *   ""        => false
 *
 * Importance: Prevents invalid or out-of-range input from being processed.
 */
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
