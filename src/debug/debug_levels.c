/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_levels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 22:57:34 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

const char	*get_debug_level_name(int mode)
{
	if (is_debug_level_mode(mode, MODE_STEP_DEBUG))
		return ("Step-by-step");
	else if (is_debug_level_mode(mode, MODE_VERBOSE_DEBUG))
		return ("Verbose");
	else if (is_debug_level_mode(mode, MODE_STATS_DEBUG))
		return ("Statistics");
	else if (is_debug_level_mode(mode, MODE_FULL_DEBUG))
		return ("Full debug");
	else
		return ("Evaluation");
}

void	enable_debug_mode(void)
{
	ft_printf("🐛 Legacy debug mode enabled\n");
}
