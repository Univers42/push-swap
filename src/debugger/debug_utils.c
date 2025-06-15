/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 22:57:31 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debugger.h"

void	debug_print_algorithm_start(const char *algorithm_name, int total_size)
{
	(void)algorithm_name;
	(void)total_size;
}

void	debug_print_algorithm_end(const char *algorithm_name, t_ps *data)
{
	(void)algorithm_name;
	(void)data;
}

void	debug_pause_if_step_mode(void)
{
	char	buffer[10];

	if (debug_is_enabled())
	{
		ft_printf("Press Enter to continue (or 'q' to quit): ");
		if (read(STDIN_FILENO, buffer, sizeof(buffer)) > 0)
		{
			if (buffer[0] == 'q' || buffer[0] == 'Q')
				exit(0);
		}
	}
}
