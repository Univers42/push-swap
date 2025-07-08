/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:02:16 by codespace         #+#    #+#             */
/*   Updated: 2025/07/08 18:38:27 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef TRACKER_H
# define TRACKER_H

// Forward declarations to avoid circular dependencies
typedef struct s_ps t_ps;
typedef enum e_op t_op;
typedef struct s_list t_list;

// Basic operations
void		pa(t_ps *data);
void		pb(t_ps *data);
void		sa(t_ps *data);
void		sb(t_ps *data);
void		ss(t_ps *data);
void		ra(t_ps *data);
void		rb(t_ps *data);
void		rr(t_ps *data);
void		rra(t_ps *data);
void		rrb(t_ps *data);
void		rrr(t_ps *data);

// Operation management
void		save_op(t_ps *data, t_op op);
void		increment_op_count(t_ps *data);
void		print_operations(t_list *head);
const char	*op_to_string(t_op op);

# endif