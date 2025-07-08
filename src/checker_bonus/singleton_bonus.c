/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:05:00 by codespace         #+#    #+#             */
/*   Updated: 2025/07/08 20:14:03 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

#if VISUALIZE == 1
# include "visualizer.h"

void	*get_checker_context(void)
{
	return (get_test_context());
}



void	run_algorithm_with_visualization(t_ps *ps, void (*algorithm)(t_ps *))
{
	ft_printf("🎬 Algorithm visualization available in checker mode\n");
	ft_printf("Use: ./push_swap args | ./checker args\n");
	ft_printf("Then choose 'y' for visualization\n");
	
	(void)ps;
	(void)algorithm;
}

#else

void	*get_checker_context(void)
{
	static int	dummy = 0;
	return (&dummy);
}

void	free_stack(t_stack *stack)
{
	(void)stack;
}

bool	is_sorted(t_stack *stack)
{
	(void)stack;
	return (false);
}

t_ps	*create_ps_copy(t_ps *original)
{
	(void)original;
	return (NULL);
}

#endif
