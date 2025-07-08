/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#if VISUALIZE == 1
# include "visualizer.h"

t_test_context	*get_test_context(void)
{
	static t_test_context	context = {
		.operations = NULL,
		.last_op = NULL,
		.op_count = 0,
		.is_recording = 0,
		.delay_ms = 50,
		.verbose_mode = 0,
		.test_ps = NULL
	};
	
	return (&context);
}

#else

// Stub implementation when visualization is disabled
typedef struct s_dummy_context
{
	int	dummy;
}	t_dummy_context;

void	*get_test_context(void)
{
	static t_dummy_context	dummy = {0};
	return (&dummy);
}

#endif
