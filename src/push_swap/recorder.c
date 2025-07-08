/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recorder.c                                         :+:      :+:    :+:   */
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

void	init_recorder(void)
{
	t_test_context	*ctx;

	ctx = get_test_context();
	cleanup_recorder();
	ctx->operations = NULL;
	ctx->last_op = NULL;
	ctx->op_count = 0;
	ctx->is_recording = 1;
}

void	record_operation(const char *operation)
{
	t_test_context	*ctx;
	t_operation		*new_op;

	ctx = get_test_context();
	if (!ctx->is_recording || !operation)
		return ;
	new_op = malloc(sizeof(t_operation));
	if (!new_op)
		return ;
	new_op->name = ft_strdup(operation);
	new_op->next = NULL;
	if (!ctx->operations)
	{
		ctx->operations = new_op;
		ctx->last_op = new_op;
	}
	else
	{
		ctx->last_op->next = new_op;
		ctx->last_op = new_op;
	}
	ctx->op_count++;
}

void	cleanup_recorder(void)
{
	t_test_context	*ctx;
	t_operation		*current;
	t_operation		*next;

	ctx = get_test_context();
	current = ctx->operations;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current);
		current = next;
	}
	ctx->operations = NULL;
	ctx->last_op = NULL;
	ctx->op_count = 0;
}

void	start_recording(void)
{
	t_test_context	*ctx;

	ctx = get_test_context();
	ctx->is_recording = 1;
}

void	stop_recording(void)
{
	t_test_context	*ctx;

	ctx = get_test_context();
	ctx->is_recording = 0;
}

int	is_recording(void)
{
	t_test_context	*ctx;

	ctx = get_test_context();
	return (ctx->is_recording);
}

#else

// Stub implementations when visualization is disabled
void	init_recorder(void) {}
void	record_operation(const char *operation) { (void)operation; }
void	cleanup_recorder(void) {}
void	start_recording(void) {}
void	stop_recording(void) {}
int		is_recording(void) { return (0); }

#endif
