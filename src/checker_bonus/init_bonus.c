/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syzygy <syzygy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 01:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/19 17:57:14 by syzygy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static void	validate_arguments(int argc, char **argv);
static int	*parse_numbers(int argc, char **argv);

/**
 * parse validation of arguments...
 * convert_numbers...
 * detect error of duplication...
 * if all is good setup_stacks
 */
void	initialize_checker_data(t_ps *data, int argc, char **argv)
{
	int	*raw_numbers;

	if (argc <= 1)
		exit(0);
	argc--;
	argv++;
	validate_arguments(argc, argv);
	raw_numbers = parse_numbers(argc, argv);
	if (detect_dup(raw_numbers, argc))
	{
		free(raw_numbers);
		ft_putendl_fd("Error", 2);
		exit(255);
	}
	checker_setup_stacks(data, raw_numbers, argc);
	free(raw_numbers);
}

/**
 * This function in the main entry point of validity checking
 * of format numbers recognized as numbers and nothing else
 * if a format is not correct, it would give back an error
 * @param argc count the argumnent
 * @param argv	teh arguments list itself
 * @return void
 */
static void	validate_arguments(int argc, char **argv)
{
	int	i;

	i = -1;
	while (++i < argc)
	{
		if (!validate_numeric_argument(argv[i]))
			(ft_putendl_fd("Error", 2), exit(FATAL_ERROR));
	}
}

/**
 * The parse_numbers function is jsut here to allocate
 * raw numbers into the lists of arguments
 * and of course convert them into the good format
 * atoi is chosen because we're contrained to INT_MAX
 */
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
	i = -1;
	while (++i < argc)
		raw_numbers[i] = ft_atoi(argv[i]);
	return (raw_numbers);
}

/**
 * this function is needed to initialize the stack data structures
 * (`stack_a` and `stack_b`) for our checker program
 * it does the following
 * 
 * Allocates memory for both stacks (`a` and `b`)
 *  based on the nb of input args
 * set init values for stack prop: cpct, top, bottom, count elem
 * fils stack_a with the input numbers (converted to ranks)
 * init_b as empty
 * prepares operation tracking if needed
 */
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
		(ft_putendl_fd("Error", 2), exit(255));
	}
	ft_memset(data, 0, sizeof(t_ps *));
	data->a.capacity = argc;
	data->b.capacity = argc;
	data->a.bottom = argc - 1;
	data->a.element_count = argc;
	convert_numbers_to_ranks(raw_numbers, data->a.stack, argc);
}
