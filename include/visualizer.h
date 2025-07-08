/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/08 18:38:28 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

# include <stdbool.h>

// Forward declarations to avoid circular dependencies
typedef struct s_ps t_ps;
typedef struct s_stack t_stack;

// Operation tracking structure
typedef struct s_operation
{
	char				*name;
	struct s_operation	*next;
}	t_operation;

// Test context for visualization
typedef struct s_test_context
{
	t_operation	*operations;
	t_operation	*last_op;
	int			op_count;
	int			is_recording;
	int			delay_ms;
	int			verbose_mode;
	t_ps		*test_ps;
}	t_test_context;

// Visualization functions
void	run_algorithm_with_visualization(t_ps *ps, void (*algorithm)(t_ps *));
void	show_frame(t_ps *ps, const char *operation);
void	execute_operation_for_visual(t_ps *ps, const char *op);

// Recording functions
void	init_recorder(void);
void	record_operation(const char *operation);
void	cleanup_recorder(void);
void	start_recording(void);
void	stop_recording(void);
int		is_recording(void);

// Singleton context
t_test_context	*get_test_context(void);

// Stack display
void	print_single_array_stack(t_stack *stack, char name);
void	print_both_array_stacks(t_stack *stack_a, t_stack *stack_b);

// Helper functions
t_ps	*create_ps_copy(t_ps *original);
void	free_stack(t_stack *stack);
bool	is_sorted(t_stack *stack);

#endif