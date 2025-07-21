/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:27:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/21 21:30:43 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "checker_bonus.h"

// just help the function for the norminette compliance
static int	init_helper(t_ps *data, int *stack_size, int *curr_idx, int *rank)
{
	int	i;

	i = 0;
	if (!data || !data->a.stack)
		return (false);
	if (data->a.element_count != data->a.capacity)
		return (false);
	*stack_size = data->a.capacity;
	*curr_idx = data->a.top;
	*rank = 1;
	return (i);
}

/**
 * This function take data->memb to discover if the stack is finally sorted
 * or not.
 * @param data ptr to structure data.
 */
bool	is_stack_sorted(t_ps *data)
{
	int	current_index;
	int	expected_rank;
	int	stack_size;
	int	i;

	i = init_helper(data, &stack_size, &current_index, &expected_rank);
	while (expected_rank <= stack_size)
	{
		if (current_index < 0 || current_index >= data->a.capacity)
			return (false);
		if (data->a.stack[current_index] != expected_rank)
			return (false);
		expected_rank++;
		current_index = move_down(&data->a, current_index);
		i++;
		if (i > stack_size)
			return (false);
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
