/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:56:05 by codespace         #+#    #+#             */
/*   Updated: 2025/07/18 16:26:00 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// PARSER FUNCTIONS
bool		is_stack_sorted(t_ps *data);
bool		validate_numeric_argument(char *arg);
bool		detect_duplicates_optimized(t_ps *data, int *numbers, int size);
bool		detect_duplicates_with_sorting(int *numbers, int size);
void		efficient_sort(int *arr, int size);

#endif