/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:25:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 22:47:55 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	is_algorithm_mode(int mode, int algo)
{
	return ((mode & MODE_ALGORITHM_MASK) == algo);
}

bool	is_debug_level_mode(int mode, int lvl)
{
	return ((mode & MODE_DEBUG_MASK) == lvl);
}

bool	has_debug_mode(int mode)
{
	return ((mode & 0x10) != 0);
}

bool	has_stats_mode(int mode)
{
	return (has_debug_mode(mode));
}

bool	has_verbose_mode(int mode)
{
	return (has_debug_mode(mode));
}
