/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:56:05 by codespace         #+#    #+#             */
/*   Updated: 2025/07/21 21:48:21 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// PARSER FUNCTIONS
bool	is_stack_sorted(t_ps *data);
bool	validate_numeric_argument(char *op);
bool	detect_dup(int *numbers, int size);

#endif