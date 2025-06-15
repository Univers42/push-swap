/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:27:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 14:58:23 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	calculate_value_range(int *numbers, int size);
static bool	detect_duplicates_with_hash(int *numbers, int size,
				char *hash_table, int range);

bool	verify_stack_is_sorted(t_ps *data)
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
		current_index = calculate_next_down_index(&data->a, current_index);
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

bool	detect_duplicates_optimized(t_ps *data, int *numbers, int size)
{
	int		range;
	char	*hash_table;
	bool	has_duplicate;

	(void)data;
	range = calculate_value_range(numbers, size);
	if (range > HASH_TABLE_THRESHOLD)
		return (detect_duplicates_with_sorting(numbers, size));
	hash_table = ft_calloc(range, sizeof(char));
	if (!hash_table)
		return (true);
	has_duplicate = detect_duplicates_with_hash(numbers, size, hash_table,
			range);
	free(hash_table);
	return (has_duplicate);
}

static int	calculate_value_range(int *numbers, int size)
{
	int	i;
	int	min_val;
	int	max_val;

	min_val = numbers[0];
	max_val = numbers[0];
	i = 1;
	while (i < size)
	{
		if (numbers[i] < min_val)
			min_val = numbers[i];
		if (numbers[i] > max_val)
			max_val = numbers[i];
		i++;
	}
	return (max_val - min_val + 1);
}

static bool	detect_duplicates_with_hash(int *numbers, int size,
			char *hash_table, int range)
{
	int	i;
	int	min_val;
	int	index;

	min_val = numbers[0];
	i = 1;
	while (i < size)
	{
		if (numbers[i] < min_val)
			min_val = numbers[i];
		i++;
	}
	i = 0;
	while (i < size)
	{
		index = numbers[i] - min_val;
		if (hash_table[index])
			return (true);
		hash_table[index] = 1;
		i++;
	}
	(void)range;
	return (false);
}
