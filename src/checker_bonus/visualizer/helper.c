/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:05:54 by codespace         #+#    #+#             */
/*   Updated: 2025/07/09 19:44:36 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

#if VISUALIZE == 1

# include "visualizer_bonus.h"

const char	*op_to_string(t_op op)
{
	static const char	*op_strings[] = {
	[OP_NULL] = "null_op",
	[OP_PA] = "pa",
	[OP_PB] = "pb",
	[OP_RA] = "ra",
	[OP_RB] = "rb",
	[OP_RR] = "rr",
	[OP_RRA] = "rra",
	[OP_RRB] = "rrb",
	[OP_RRR] = "rrr",
	[OP_SA] = "sa",
	[OP_SB] = "sb",
	[OP_SS] = "ss"
	};

	if (op < 0 || op >= (sizeof(op_strings) / sizeof(op_strings[0])))
		return ("invalid_op");
	return (op_strings[op]);
}

bool	is_piped_input(void)
{
	return (!isatty(STDIN_FILENO));
}

static void	process_visualization_line(t_ps *data, char *line, int *step)
{
	t_op	operation;
	char	step_info[100];

	operation = string_to_op(line);
	if (operation == OP_NULL)
	{
		free(line);
		checker_error_exit(data);
	}
	record_operation(line);
	execute_checker_operation(data, operation);
	snprintf(step_info, sizeof(step_info), "Step %d: %s", *step, line);
	show_frame(data, step_info);
	ft_printf("\n");
	(*step)++;
}

void	checker_main_logic(t_ps *data)
{
	if (!isatty(STDIN_FILENO))
		ask_for_visualization(data);
	else
		checker_main_logic_core(data);
}

void	checker_main_logic_core(t_ps *data)
{
	read_and_execute_operations(data);
	if (check_if_stack_is_empty(&data->b) && verify_stack_is_sorted(data))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
}

void	ask_for_visualization(t_ps *data)
{
	char	choice;
	FILE	*tty;

	ft_printf("🎬 Push_swap Checker Visualization\n");
	ft_printf("Stack size: %d\n", get_current_stack_size(&data->a));
	ft_printf("\nVisualize operations step by step? (y/n): ");
	fflush(stdout);
	tty = fopen("/dev/tty", "r");
	if (tty && fscanf(tty, " %c", &choice) == 1 && 
		(choice == 'y' || choice == 'Y'))
	{
		fclose(tty);
		run_checker_with_visualization(data);
	}
	else
	{
		if (tty)
			fclose(tty);
		checker_main_logic_core(data);
	}
}

void	run_checker_with_visualization(t_ps *data)
{
	char			*line;
	int				step;
	t_test_context	*ctx;

	ft_printf("\n🎬 Push_swap Visualizer\n");
	ft_printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	ft_printf("Stack size: %d | Auto-visualization mode\n",
		get_current_stack_size(&data->a));
	ft_printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
	init_recorder();
	start_recording();
	show_frame(data, "🏁 INITIAL STATE");
	ft_printf("\n");
	step = 1;
	line = get_next_line(STDIN_FILENO);
	while (line != NULL)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		process_visualization_line(data, line, &step);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
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
	ctx = get_test_context();
	ft_printf("\n📊 Total operations: %d\n", ctx->op_count);
	ft_printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	stop_recording();
	cleanup_recorder();
}


#endif