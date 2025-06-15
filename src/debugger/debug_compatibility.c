/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_compatibility.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 22:57:33 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debugger.h"

void	set_debug_mode(int mode)
{
	debug_init(mode);
}

bool	is_debug_mode_enabled(void)
{
	return (debug_is_enabled());
}

bool	is_verbose_mode_enabled(void)
{
	return (false);
}

bool	is_stats_mode_enabled(void)
{
	return (false);
}

bool	debug_level_at_least(int level)
{
	(void)level;
	return (debug_is_enabled());
}
