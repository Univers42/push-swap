/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:55:38 by ugerkens          #+#    #+#             */
/*   Updated: 2025/06/15 23:11:05 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_BONUS_H
# define CHECKER_BONUS_H

# include "stack_core.h"
# include "stack_operations.h"
# include "stack_utils.h"

char	*get_next_line(int fd);

int		main(int argc, char *argv[]);
void	initialize_checker_data(t_ps *data, int argc, char **argv);
void	read_and_execute_operations(t_ps *data);
void	execute_checker_operation(t_ps *data, t_op operation);
void	checker_cleanup_and_exit(t_ps *data);
void	checker_error_exit(t_ps *data);
void	checker_setup_stacks(t_ps *data, int *raw_numbers, int argc);

t_op	string_to_op(const char *str);

// Checker-specific operations (no tracking)
void	checker_push(t_stack *src, t_stack *dest);
void	checker_swap(t_stack *stk);
void	checker_rotate(t_stack *stk);
void	checker_r_rotate(t_stack *stk);

#endif