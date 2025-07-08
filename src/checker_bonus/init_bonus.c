/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 01:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 23:13:31 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static void	validate_arguments(int argc, char **argv);
static int	*parse_numbers(int argc, char **argv);

void	initialize_checker_data(t_ps *data, int argc, char **argv)
{
	int	*raw_numbers;

	if (argc <= 1)
		exit(0);
	argc--;
	argv++;
	validate_arguments(argc, argv);
	raw_numbers = parse_numbers(argc, argv);
	if (detect_duplicates_with_sorting(raw_numbers, argc))
	{
		free(raw_numbers);
		ft_putendl_fd("Error", 2);
		exit(255);
	}
	checker_setup_stacks(data, raw_numbers, argc);
	free(raw_numbers);
}

static void	validate_arguments(int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		if (!validate_numeric_argument(argv[i]))
		{
			ft_putendl_fd("Error", 2);
			exit(255);
		}
		i++;
	}
}

static int	*parse_numbers(int argc, char **argv)
{
	int	*raw_numbers;
	int	i;

	raw_numbers = malloc(sizeof(int) * argc);
	if (!raw_numbers)
	{
		ft_putendl_fd("Error", 2);
		exit(255);
	}
	i = 0;
	while (i < argc)
	{
		raw_numbers[i] = ft_atoi(argv[i]);
		i++;
	}
	return (raw_numbers);
}

void	checker_setup_stacks(t_ps *data, int *raw_numbers, int argc)
{
	data->a.stack = malloc(sizeof(int) * argc);
	data->b.stack = malloc(sizeof(int) * argc);
	if (!data->a.stack || !data->b.stack)
	{
		if (data->a.stack)
			free(data->a.stack);
		if (data->b.stack)
			free(data->b.stack);
		ft_putendl_fd("Error", 2);
		exit(255);
	}
	data->a.capacity = argc;
	data->b.capacity = argc;
	data->a.top = 0;
	data->b.top = 0;
	data->a.bottom = argc - 1;
	data->b.bottom = 0;
	data->a.element_count = argc;
	data->b.element_count = 0;
	convert_numbers_to_ranks(raw_numbers, data->a.stack, argc);
	data->op_list = NULL;
	data->op_count = 0;
	data->op_capacity = 0;
}
