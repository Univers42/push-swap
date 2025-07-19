/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syzygy <syzygy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:56:49 by ugerkens          #+#    #+#             */
/*   Updated: 2025/07/19 16:23:40 by syzygy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

/**
 * main entry point logic of the checker
 * The checker has to parse some rules:
 * - check dupliacates
 * - check validity of arguments (just numbers and if arg ==1 then Good)
 * - read the stdin to get the movements expected
 * - The movements are traces one by one to verify if the stack is sorted
 * - Once the movements done, the checker verify if the list is sorted
 * - if sorted ? then OK : KO
 */
int	main(int argc, char *argv[])
{
	t_ps	data;

	if (argc == 1)
		exit(EXIT_SUCCESS);
	initialize_checker_data(&data, argc, argv);
	checker_main_logic(&data);
	destroy(&data);
	free_all_gnl();
	exit(EXIT_SUCCESS);
}

/**
 * This function reads line by line in stdin thanks to
 * the use of the funciton get_next_line
 * Then each iterations when The operations has been added
 * we execute checker_operation
 */
void	rx_ops(t_ps *data)
{
	char	*line;
	t_op	operation;

	line = get_next_line(STDIN_FILENO);
	while (line != NULL)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		operation = tr_ops_code(line);
		if (operation == OP_NULL)
		{
			free(line);
			checker_error_exit(data);
		}
		run_op(data, operation);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
}

/**
 * free either one of the stack or both depending on states
 */
void	destroy(t_ps *data)
{
	if (data->a.stack)
		free(data->a.stack);
	if (data->b.stack)
		free(data->b.stack);
}

/**
 * display an error. and exit with the code 255
 */
void	checker_error_exit(t_ps *data)
{
	destroy(data);
	free_all_gnl();
	ft_putendl_fd("Error", 2);
	exit(FATAL_ERROR);
}


/**
 * this function
 */
__attribute__((weak))
void	checker_main_logic(t_ps *data)
{
	rx_ops(data);
	if (check_if_stack_is_empty(&data->b) && is_stack_sorted(data))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
}
