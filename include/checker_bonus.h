/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:55:38 by ugerkens          #+#    #+#             */
/*   Updated: 2025/07/17 01:34:13 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_BONUS_H
# define CHECKER_BONUS_H

# include "push_swap.h"
# include "visualizer_bonus.h"
# include <fcntl.h>
# include <unistd.h>

# define STACK_A_BIT	0x1
# define STACK_B_BIT	0x2
# define DUAL_OP_BIT	0x4

typedef struct s_op_exec
{
	void	(*single_op)(t_stack *);
	void	(*dual_op)(t_stack *, t_stack *);
	int		stack_mask;
	int		is_dual;
}	t_op_exec;

char	*get_next_line(int fd);

int		main(int argc, char *argv[]);
void	initialize_checker_data(t_ps *data, int argc, char **argv);
void	read_and_execute_operations(t_ps *data);
void	execute_checker_operation(t_ps *data, t_op operation);
void	checker_cleanup_and_exit(t_ps *data);
void	checker_error_exit(t_ps *data);
void	checker_setup_stacks(t_ps *data, int *raw_numbers, int argc);
void	checker_main_logic(t_ps *data);

# if VISUALIZE == 1

void	checker_main_logic_core(t_ps *data);
# endif

t_op	string_to_op(const char *str);
void	error_read_op(t_ps *data, char *line);

// Checker-specific operations (no tracking)
void	checker_push(t_stack *src, t_stack *dest);
void	checker_swap(t_stack *stk);
void	checker_rotate(t_stack *stk);
void	checker_r_rotate(t_stack *stk);

// Visualization functions (when VISUALIZE is enabled)
# if VISUALIZE == 1

bool	is_piped_input(void);						//
void	ask_for_visualization(t_ps *data);			//
void	run_checker_with_visualization(t_ps *data);	//
# endif

#endif