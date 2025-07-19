/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syzygy <syzygy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:56:05 by codespace         #+#    #+#             */
/*   Updated: 2025/07/19 15:19:16 by syzygy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// PARSER FUNCTIONS
bool		is_stack_sorted(t_ps *data);
bool		validate_numeric_argument(char *op);
bool        detect_dup(int *numbers, int size);

#endif