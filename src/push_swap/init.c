/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:08:35 by ugerkens          #+#    #+#             */
/*   Updated: 2025/07/18 16:25:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_engine_ps(t_ps *data, int argc, char **argv)
{
	data->op_list = NULL;
	if (argc <= 1)
		cleanup_and_exit_with_error(data);
	--argc;
	allocate_and_init_stack(data, &data->a, argc);
	allocate_and_init_stack(data, &data->b, argc);
	populate_stack_with_ranks(data, &data->a, argc, ++argv);
	data->op_count = 0;
	data->op_capacity = INITIAL_OP_CAPACITY;
}

void	allocate_and_init_stack(t_ps *data, t_stack *stk, int capacity)
{
	stk->stack = malloc(sizeof(int) * capacity);
	if (!stk->stack)
		cleanup_and_exit_with_error(data);
	stk->top = 0;
	stk->bottom = 0;
	stk->capacity = capacity;
	stk->element_count = 0;
	ft_memset(stk->stack, 0, sizeof(int) * capacity);
}
