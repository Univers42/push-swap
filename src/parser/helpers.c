/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 23:15:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/19 03:34:14 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	detect_dup(int *numbers, int size)
{
	int		*sorted_copy;
	int		i;
	bool	has_duplicate;

	sorted_copy = malloc(sizeof(int) * size);
	if (!sorted_copy)
		return (true);
	ft_memcpy(sorted_copy, numbers, sizeof(int) * size);
	ft_quick_sort(sorted_copy,0, size - 1);
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
