/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cv_stack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syzygy <syzygy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:09:08 by ugerkens          #+#    #+#             */
/*   Updated: 2025/07/19 15:20:47 by syzygy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	assign_element_ranks(int *numbers, int *rank, int *sorted,
				int size);
static int	binary_search_for_rank(int *sorted, int size, int target);
static void	validate_and_convert_args(t_ps *data, int *raw_numbers,
				int size, char **arg);

void	populate_stack_with_ranks(t_ps *data, t_stack *stk, int size,
		char **arg)
{
	int	*raw_numbers;

	raw_numbers = malloc(sizeof(int) * size);
	if (!raw_numbers)
		cleanup_and_exit_with_error(data);
	validate_and_convert_args(data, raw_numbers, size, arg);
	if (detect_dup(raw_numbers, size))
	{
		free(raw_numbers);
		cleanup_and_exit_with_error(data);
	}
	convert_numbers_to_ranks(raw_numbers, stk->stack, size);
	stk->bottom = size - 1;
	stk->element_count = size;
	free(raw_numbers);
}

static void	validate_and_convert_args(t_ps *data, int *raw_numbers,
		int size, char **arg)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (!validate_numeric_argument(arg[i]))
		{
			free(raw_numbers);
			cleanup_and_exit_with_error(data);
		}
		raw_numbers[i] = ft_atoi(arg[i]);
		i++;
	}
}

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
