/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 23:15:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/09 17:45:26 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	detect_duplicates_with_sorting(int *numbers, int size)
{
	int		*sorted_copy;
	int		i;
	bool	has_duplicate;

	sorted_copy = malloc(sizeof(int) * size);
	if (!sorted_copy)
		return (true);
	ft_memcpy(sorted_copy, numbers, sizeof(int) * size);
	efficient_sort(sorted_copy, size);
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

void	efficient_sort(int *arr, int size)
{
	if (size > 1)
		ft_quick_sort(arr, 0, size - 1);
}
