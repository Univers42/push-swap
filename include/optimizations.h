/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimizations.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:15:23 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:15:24 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIMIZATIONS_H
# define OPTIMIZATIONS_H

# include "algorithms.h"

// Pattern recognition optimizations
void		easy_sort(t_ps *data, t_chunk *to_sort);
void		split_max_reduction(t_ps *data, t_chunk *max);
bool		a_partly_sort(t_ps *data, int from);
bool		is_consecutive(int a, int b, int c, int d);
void		chunk_to_the_top(t_ps *data, t_chunk *to_sort);

// Post-processing optimizations (exact working version interface)
void		post_sort_optimization(t_ps *data);
void		eliminate_neutral_op(t_ps *data);
void		merge_op(t_ps *data);
void		remove_op_from_list(t_list **list, t_list *to_remove);
void		remove_op(t_list *to_delete);

#endif
