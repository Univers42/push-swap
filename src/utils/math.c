/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/08 14:56:41 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	partition_int(int *arr, int low, int high);

void	ft_swap(void *a, void *b, size_t size)
{
	char	*ptr_a;
	char	*ptr_b;
	char	tmp;
	size_t	i;

	ptr_a = (char *)a;
	ptr_b = (char *)b;
	i = 0;
	while (i < size)
	{
		tmp = ptr_a[i];
		ptr_a[i] = ptr_b[i];
		ptr_b[i] = tmp;
		i++;
	}
}

int	ft_sqrt(int nb)
{
	int	sqrt_val;

	if (nb < 0)
		return (0);
	if (nb == 0 || nb == 1)
		return (nb);
	sqrt_val = 1;
	while (sqrt_val * sqrt_val <= nb)
		sqrt_val++;
	return (sqrt_val - 1);
}

//already have it normallly into the lib
void	quick_sort_int(int *arr, int low, int high)
{
	int	pivot;

	if (low < high)
	{
		pivot = partition_int(arr, low, high);
		quick_sort_int(arr, low, pivot - 1);
		quick_sort_int(arr, pivot + 1, high);
	}
}

static int	partition_int(int *arr, int low, int high)
{
	int	pivot;
	int	i;
	int	j;

	pivot = arr[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (arr[j] < pivot)
		{
			i++;
			ft_swap(&arr[i], &arr[j], sizeof(int));
		}
		j++;
	}
	ft_swap(&arr[i + 1], &arr[high], sizeof(int));
	return (i + 1);
}
