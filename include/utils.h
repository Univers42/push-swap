/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:18:55 by codespace         #+#    #+#             */
/*   Updated: 2025/07/19 02:57:17 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include <limits.h>
# include "stack.h"

// Forward declarations
typedef struct s_ps		t_ps;

// Hash table threshold for optimization
# define HASH_TABLE_THRESHOLD 100000
# define INITIAL_OP_CAPACITY 100
# define MAX_OPERATIONS 10000

// Math utilities
int			ft_sqrt(int num);

// Stack utilities
int			get_items(t_stack *stk, int position);
int			get_stack_size(t_stack *stk);
int			move_up(t_stack *stk, int index);
int			move_down(t_stack *stk, int index);

//CLEANUP
void		cleanup_and_exit_with_error(t_ps *data);
void		release_mem(t_ps *data);
void		remove_op_from_list(t_list **list, t_list *to_remove);

int			find_min(t_stack *stack);
bool		is_consecutive(int a, int b, int c, int d);
#endif