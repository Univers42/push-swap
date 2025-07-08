/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:56:49 by ugerkens          #+#    #+#             */
/*   Updated: 2025/07/08 21:01:45 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#ifndef VISUALIZE
# define VISUALIZE 0
#endif

#if VISUALIZE == 1
# include "visualizer.h"
static void	run_checker_with_visualization(t_ps *data);
static void	ask_for_visualization(t_ps *data);
static bool	is_piped_input(void);
#endif

int	main(int argc, char *argv[])
{
	t_ps	data;

	if (argc <= 1)
		exit(EXIT_SUCCESS);
	initialize_checker_data(&data, argc, argv);
	
#if VISUALIZE == 1
	// Automatically enable visualization when receiving piped input
	if (is_piped_input())
	{
		run_checker_with_visualization(&data);
	}
	else
	{
		// Interactive mode - ask for visualization
		ask_for_visualization(&data);
	}
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
		
#if VISUALIZE == 1
		if (is_recording())
			record_operation(line);
#endif
		
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
static bool	is_piped_input(void)
{
	int	flags;
	
	// Check if stdin is a terminal
	if (!isatty(STDIN_FILENO))
		return (true);
	
	// Additional check: see if data is available without blocking
	flags = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
	
	char	test;
	int		result = read(STDIN_FILENO, &test, 0);
	
	fcntl(STDIN_FILENO, F_SETFL, flags); // Restore original flags
	
	return (result >= 0);
}

static void	ask_for_visualization(t_ps *data)
{
	char	choice;
	
	ft_printf("🎬 Push_swap Checker Visualization\n");
	ft_printf("Stack size: %d\n", get_current_stack_size(&data->a));
	ft_printf("\nVisualize operations step by step? (y/n): ");
	
	if (scanf(" %c", &choice) == 1 && (choice == 'y' || choice == 'Y'))
	{
		run_checker_with_visualization(data);
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

static void	run_checker_with_visualization(t_ps *data)
{
	ft_printf("\n🎬 Push_swap Visualizer\n");
	ft_printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	ft_printf("Stack size: %d | Auto-visualization mode\n", get_current_stack_size(&data->a));
	ft_printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
	
	// Initialize recorder
	init_recorder();
	start_recording();
	
	// Show initial state
	show_frame(data, "🏁 INITIAL STATE");
	ft_printf("\n");
	
	// Read and execute operations with visualization
	char	*line;
	t_op	operation;
	int		step = 1;
	
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
		
		// Record and execute with visualization
		record_operation(line);
		execute_checker_operation(data, operation);
		
		// Show current state
		char step_info[100];
		snprintf(step_info, sizeof(step_info), "Step %d: %s", step++, line);
		show_frame(data, step_info);
		ft_printf("\n");
		
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	
	// Show final result
	ft_printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	if (check_if_stack_is_empty(&data->b) && verify_stack_is_sorted(data))
	{
		show_frame(data, "✅ FINAL STATE - OK");
		ft_printf("\n🎉 SUCCESS: Stack is properly sorted!\n");
	}
	else
	{
		show_frame(data, "❌ FINAL STATE - KO");
		ft_printf("\n❌ FAILURE: Stack is not properly sorted!\n");
	}
	
	// Show statistics
	t_test_context *ctx = get_test_context();
	ft_printf("\n📊 Total operations: %d\n", ctx->op_count);
	ft_printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	
	stop_recording();
	cleanup_recorder();
}
#endif
