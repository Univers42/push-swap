/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:56:49 by ugerkens          #+#    #+#             */
/*   Updated: 2025/06/16 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

#ifndef VISUALIZE
# define VISUALIZE 0
#endif

#if VISUALIZE == 1
# include "visualizer.h"
void	run_checker_with_visualization(t_ps *data);
#endif

int	main(int argc, char *argv[])
{
	t_ps	data;

	if (argc <= 1)
		exit(EXIT_SUCCESS);
	initialize_checker_data(&data, argc, argv);
	
#if VISUALIZE == 1
	run_checker_with_visualization(&data);
#else
	read_and_execute_operations(&data);
	if (check_if_stack_is_empty(&data.b) && verify_stack_is_sorted(&data))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
#endif
	
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

#if VISUALIZE == 1
void	run_checker_with_visualization(t_ps *data)
{
	char	choice;
	
	ft_printf("🎬 Checker Visualization Mode\n");
	ft_printf("Stack size: %d\n", get_current_stack_size(&data->a));
	ft_printf("\nVisualize operations? (y/n): ");
	
	if (scanf(" %c", &choice) == 1 && (choice == 'y' || choice == 'Y'))
	{
		ft_printf("\nPress Enter to start...\n");
		getchar();
		getchar();
		
		init_recorder();
		start_recording();
		show_frame(data, "🏁 INITIAL STATE");
		
		read_and_execute_operations(data);
		
		stop_recording();
		
		if (check_if_stack_is_empty(&data->b) && verify_stack_is_sorted(data))
			show_frame(data, "✅ OK - Stack is sorted!");
		else
			show_frame(data, "❌ KO - Stack is not sorted!");
			
		cleanup_recorder();
	}
	else
	{
		read_and_execute_operations(data);
		if (check_if_stack_is_empty(&data->b) && verify_stack_is_sorted(data))
			ft_printf("OK\n");
		else
			ft_printf("KO\n");
	}
}
#endif
