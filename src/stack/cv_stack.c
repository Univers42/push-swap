/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cv_stack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 01:49:31 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/22 04:34:05 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	validate_and_convert_args(t_ps *data, int *raw_numbers,
				int size, char **arg);
static void	assign_element_ranks(int *numbers, int *rank, int *sorted,
				int size);
static int	binary_search_for_rank(int *sorted, int size, int target);

/**
 * @brief Populates a stack with rank values based on input arguments.
 *
 * This function parses the input arguments, validates them,
 * checks for duplicates,
 * and fills the stack with the rank (sorted order) of each number.
 *
 * Example:
 *   Input: arg = ["40", "10", "30"]
 *   After: stk->stack = [3, 1, 2]
 * ======(since 10 is smallest, 30 is second, 40 is third)
 *
 * Importance: Ensures the stack contains normalized values
 * for efficient sorting.
 */
void	populate_stack_with_ranks(t_ps *data, t_stack *stk, int size,
		char **arg)
{
	int	*raw_numbers;

	raw_numbers = malloc(sizeof(int) * size);
	if (!raw_numbers)
		cleanup_and_exit_with_error(data);
	validate_and_convert_args(data, raw_numbers, size, arg);
	if (detect_dup(raw_numbers, size))
		(free(raw_numbers), cleanup_and_exit_with_error(data));
	convert_numbers_to_ranks(raw_numbers, stk->stack, size);
	stk->bottom = size - 1;
	stk->element_count = size;
	free(raw_numbers);
}

/**
 * @brief Validates and converts argument strings to integers.
 *
 * Checks that each argument is a valid integer and converts it to int.
 * If any argument is invalid, frees memory and exits.
 *
 * Example:
 *   arg = ["42", "-7", "abc"] -> exits with error on "abc"
 */
static void	validate_and_convert_args(t_ps *data, int *raw_numbers,
		int size, char **arg)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (!validate_numeric_argument(arg[i]))
			(free(raw_numbers), cleanup_and_exit_with_error(data));
		raw_numbers[i] = ft_atoi(arg[i]);
		i++;
	}
}

/**
 * @brief Converts an array of numbers to their rank order.
 *
 * For each number, finds its position in the sorted array and assigns
 * its rank (1-based) to the output array.
 *
 * Example:
 *   numbers = [40, 10, 30]
 *   sorted_numbers = [10, 30, 40]
 *   Output: rank = [3, 1, 2]
 */
void	convert_numbers_to_ranks(int *numbers, int *rank, int size)
{
	int	*sorted_numbers;

	sorted_numbers = malloc(sizeof(int) * size);
	if (!sorted_numbers)
		return ;
	ft_memcpy(sorted_numbers, numbers, sizeof(int) * size);
	ft_quick_sort(sorted_numbers, 0, size - 1);
	assign_element_ranks(numbers, rank, sorted_numbers, size);
	free(sorted_numbers);
}

/**
 * @brief Assigns rank values to each number based on sorted order.
 *
 * For each number in the input, finds its index in the sorted array and
 * assigns rank = index + 1.
 *
 * Example:
 *   numbers = [40, 10, 30], sorted = [10, 30, 40]
 *   Output: rank = [3, 1, 2]
 */
static void	assign_element_ranks(int *numbers, int *rank, int *sorted,
		int size)
{
	int	i;
	int	rank_value;

	i = 0;
	while (i < size)
	{
		rank_value = binary_search_for_rank(sorted, size, numbers[i]);
		rank[i] = rank_value + 1;
		i++;
	}
}

/**
 * @brief Performs binary search to find the rank (index) of a target value.
 *
 * Searches for the target value in the sorted array and returns its index.
 *
 * Example:
 *   sorted = [10, 30, 40], target = 30 -> returns 1
 */
static int	binary_search_for_rank(int *sorted, int size, int target)
{
	int	left;
	int	right;
	int	mid;

	left = 0;
	right = size - 1;
	while (left <= right)
	{
		mid = left + ((right - left) >> 1);
		if (sorted[mid] == target)
			return (mid);
		else if (sorted[mid] < target)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return (-1);
}
