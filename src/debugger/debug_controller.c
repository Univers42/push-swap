/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_controller.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 22:57:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debugger.h"

void	debug_init(int mode)
{
	if (has_debug_mode(mode))
		ft_printf("🐛 [DEBUG] Debug mode enabled\n");
}

void	debug_set_algorithm(const char *algorithm_name)
{
	(void)algorithm_name;
}

bool	debug_is_enabled(void)
{
	return (false);
}

void	debug_increment_step(void)
{
}
