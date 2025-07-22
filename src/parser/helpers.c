/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 01:48:40 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/22 04:27:37 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @brief Detects duplicate integers in an array.
 *
 * This function creates a sorted copy of the input array and checks for
 * consecutive equal values, indicating a duplicate.
 *
 * Example:
 *   numbers = [3, 1, 2, 4]   => returns false (no duplicates)
 *   numbers = [1, 2, 2, 3]   => returns true (duplicate 2)
 *
 * Importance: Ensures all input values are unique, as required by push_swap.
 */
bool	detect_dup(int *numbers, int size)
{
	int		*sorted_copy;
	int		i;
	bool	has_duplicate;

	sorted_copy = malloc(sizeof(int) * size);
	if (!sorted_copy)
		return (true);
	ft_memcpy(sorted_copy, numbers, sizeof(int) * size);
	ft_quick_sort(sorted_copy, 0, size - 1);
	has_duplicate = false;
	i = 0;
	while (i < size - 1)
	{
		if (sorted_copy[i] == sorted_copy[i + 1])
		{
			has_duplicate = true;
			break ;
		}
		i++;
	}
	free(sorted_copy);
	return (has_duplicate);
}
