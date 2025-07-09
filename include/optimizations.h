/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimizations.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:15:23 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/09 17:36:28 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIMIZATIONS_H
# define OPTIMIZATIONS_H

# include "stack.h"
# include "algorithms.h"

// Forward declarations
typedef struct s_ps	t_ps;

/**
 the optimizations are important part of this project, they able the compiler
 to be quicker but also to get less movement tracked when using the project
 Also the good think about this page is that this is extensible to all sort
 algorithms, making them an average much faster. Generally if One is faster
 the other will follow the same rythm. Now I didn't success to impllement
 all the idea I had for agorithm machine and the optimizations 
 can be sure optimized
 further. Anyway I've build this project so I can work on other ideas of algo
 throughout my career.. Sorting algorithm is an important step but it's even
 better if you're able to track all the datasa one by one. This is what the 
 project has to offer...
*/

// Chunk optimization functions
void		easy_sort(t_ps *data, t_chunk *to_sort);
void		redox(t_ps *data, t_chunk *max);
bool		a_partly_sort(t_ps *data, int from);
void		chunk_to_the_top(t_ps *data, t_chunk *to_sort);

// Optimization functions
void		post_sort_optimization(t_ps *data);
void		eliminate_neutral_op(t_ps *data);
void		merge_op(t_ps *data);

// Finite state machine functions
t_op		neutral_op(t_op op);
bool		op_on_same_stack(t_op ref, t_op to_check);

// Chunk sort functions
void		rec_chunk_sort(t_ps *data, t_chunk *to_sort);
void		chunk_split(t_ps *data, t_chunk *to_split, t_split_dest *dest);
#endif
