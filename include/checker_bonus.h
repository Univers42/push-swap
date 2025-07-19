/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syzygy <syzygy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:55:38 by ugerkens          #+#    #+#             */
/*   Updated: 2025/07/19 15:53:54 by syzygy           ###   ########.fr       */
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
# define FATAL_ERROR	255

typedef struct s_op_exec
{
	const char	*name;
	void		(*op_func)(t_ps *);
	int			stack_mask;
}	t_op_exec;

t_op_exec *get_op_table(void);

char	*get_next_line(int fd);

int		main(int argc, char *argv[]);
void	initialize_checker_data(t_ps *data, int argc, char **argv);
void	rx_ops(t_ps *data);
void	run_op(t_ps *data, t_op operation);
void	destroy(t_ps *data);
void	checker_error_exit(t_ps *data);
void	checker_setup_stacks(t_ps *data, int *raw_numbers, int argc);
void	checker_main_logic(t_ps *data);

# if VISUALIZE == 1

void	checker_main_logic_core(t_ps *data);
# endif

t_op	tr_ops_code(const char *str);

// Checker-specific operations (no tracking)
void	checker_push(t_stack *src, t_stack *dest);
void	checker_swap(t_stack *stk);
void	checker_rotate(t_stack *stk);
void	checker_r_rotate(t_stack *stk);

void	checker_pa(t_ps *data);
void	checker_pb(t_ps *data);
void	checker_sa(t_ps *data);
void	checker_sb(t_ps *data);
void	checker_ss(t_ps *data);
void	checker_ra(t_ps *data);
void	checker_rb(t_ps *data);
void	checker_rr(t_ps *data);
void	checker_rra(t_ps *data);
void	checker_rrb(t_ps *data);
void	checker_rrr(t_ps *data);

// Visualization functions (when VISUALIZE is enabled)
# if VISUALIZE == 1

bool	is_piped_input(void);						//
void	ask_for_visualization(t_ps *data);			//
void	run_checker_with_visualization(t_ps *data);	//
# endif

#endif