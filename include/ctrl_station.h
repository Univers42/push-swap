/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_station.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:57:07 by codespace         #+#    #+#             */
/*   Updated: 2025/07/09 17:36:27 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CTRL_STATION_H
# define CTRL_STATION_H

# include "algorithms.h"

// Forward declarations
typedef struct s_ps	t_ps;

// Function prototypes
void	select_algorithm(t_ps *data, t_algo_type type);
void		execute_algorithm(t_ps *data);
void		sort(t_ps *data);

#endif