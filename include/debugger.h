/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 22:57:31 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUGGER_H
# define DEBUGGER_H

# include "push_swap.h"

void			debug_init(int mode);
void			debug_set_algorithm(const char *algorithm_name);
bool			debug_is_enabled(void);
void			debug_increment_step(void);
void			debug_increment_operation(void);
int				debug_get_step_count(void);
int				debug_get_operation_count(void);
const char		*debug_get_algorithm_name(void);

void			debug_print_stack_state(t_ps *data, const char *context);
void			debug_print_operation(t_ps *data, const char *operation);
void			debug_print_algorithm_start(const char *algorithm_name,
					int total_size);
void			debug_print_algorithm_end(const char *algorithm_name,
					t_ps *data);
void			debug_pause_if_step_mode(void);

// Legacy compatibility functions (replacing macros)
void			set_debug_mode(int mode);
bool			is_debug_mode_enabled(void);
bool			is_verbose_mode_enabled(void);
bool			is_stats_mode_enabled(void);
bool			debug_level_at_least(int level);

#endif
