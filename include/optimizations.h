/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimizations.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:15:23 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/08 15:01:56 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIMIZATIONS_H
# define OPTIMIZATIONS_H

# include "algorithms.h"

/**
 the optimizations are important part of this project, they able the compiler
 to be quicker but also to get less movement tracked when using the project
 Also the good think about this page is that this is extensible to all sort
 algorithms, making them an average much faster. Generally if One is faster
 the other will follow the same rythm. Now I didn't success to impllement
 all the idea I had for agorithm machine and the optimizations 
 can be sure optimized
 further. Anyway I've build this project so I can work on other ideas of algorithmm
 throughout my career.. Sorting algorithm is an important step but it's even
 better if you're able to track all the datasa one by one. This is what the 
 project has to offer...
*/

// Pattern recognition optimizations
void		easy_sort(t_ps *data, t_chunk *to_sort);
void		redox(t_ps *data, t_chunk *max);
bool		a_partly_sort(t_ps *data, int from);
bool		is_consecutive(int a, int b, int c, int d);
void		chunk_to_the_top(t_ps *data, t_chunk *to_sort);

// Post-processing optimizations (exact working version interface)
void		post_sort_optimization(t_ps *data);

// Removing functions...
void		eliminate_neutral_op(t_ps *data);
void		merge_op(t_ps *data);
void		remove_op_from_list(t_list **list, t_list *to_remove);
void		remove_op(t_list *to_delete);

#endif
