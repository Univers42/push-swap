/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 23:22:18 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/18 15:10:22 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#ifndef ALGORITHM
# define ALGORITHM ALGO_CHUNK
#endif

/**
 * Main entry point of the DATA migration facility
 * the migration facility is just a set of rules and data
 * structure that enable to extend our code to the logic we need
 * this one is more a didactical way to showcase different way of thinking
 * which is really important for Engineering principles
 * The default algorithm is set to ALGO_CHUNK to do that
 */
int	main(int argc, char *argv[])
{
	t_ps	data;

	ft_memset(&data, 0, sizeof(t_ps));
	initialize_push_swap_data(&data, argc, argv);
	data.total_size = get_current_stack_size(&data.a);
	if (!verify_stack_is_sorted(&data))
	{
		select_algorithm(&data, ALGORITHM);
		execute_algorithm(&data);
		post_sort_optimization(&data);
		print_operations(data.op_list);
	}
	release_allocated_memory(&data);
	return (0);
}
