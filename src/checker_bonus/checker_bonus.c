/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:56:49 by ugerkens          #+#    #+#             */
/*   Updated: 2025/07/18 16:26:00 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

int	main(int argc, char *argv[])
{
	t_ps	data;

	if (argc <= 1)
		exit(EXIT_SUCCESS);
	initialize_checker_data(&data, argc, argv);
	checker_main_logic(&data);
	checker_cleanup_and_exit(&data);
	exit(EXIT_SUCCESS);
}

void	read_and_execute_operations(t_ps *data)
{
	char	*line;
	t_op	operation;

	line = get_next_line(STDIN_FILENO);
	while (line != NULL)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		operation = string_to_op(line);
		if (operation == OP_NULL)
		{
			free(line);
			checker_error_exit(data);
		}
		execute_checker_operation(data, operation);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
}

void	checker_cleanup_and_exit(t_ps *data)
{
	if (data->a.stack)
		free(data->a.stack);
	if (data->b.stack)
		free(data->b.stack);
}

void	checker_error_exit(t_ps *data)
{
	checker_cleanup_and_exit(data);
	ft_putendl_fd("Error", 2);
	exit(255);
}

__attribute__((weak))
void	checker_main_logic(t_ps *data)
{
	read_and_execute_operations(data);
	if (check_if_stack_is_empty(&data->b) && is_stack_sorted(data))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
}
