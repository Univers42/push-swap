/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_station.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:57:07 by codespace         #+#    #+#             */
/*   Updated: 2025/07/17 03:49:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CTRL_STATION_H
# define CTRL_STATION_H

# include "algorithms.h"
# include "push_swap.h"

// Forward declarations
typedef struct s_ps	t_ps;

// Function prototypes
void		select_algorithm(t_ps *data, t_algo_type type);
void		execute_algorithm(t_ps *data);
void		sort(t_ps *data);

#endif