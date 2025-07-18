/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:27:31 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/18 16:24:32 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	lst_clear(t_list *lst)
{
	t_list	*curr;
	t_list	*next;

	if (!lst)
		return ;
	curr = lst;
	while (curr)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
}

void	cleanup_and_exit_with_error(t_ps *data)
{
	if (data)
	{
		if (data->a.stack)
		{
			free(data->a.stack);
			data->a.stack = NULL;
		}
		if (data->b.stack)
		{
			free(data->b.stack);
			data->b.stack = NULL;
		}
		if (data->op_list)
			lst_clear(data->op_list);
	}
	ft_putendl_fd("Error", 2);
	exit(1);
}

void	release_mem(t_ps *data)
{
	if (!data)
		return ;
	if (data->a.stack)
	{
		free(data->a.stack);
		data->a.stack = NULL;
	}
	if (data->b.stack)
	{
		free(data->b.stack);
		data->b.stack = NULL;
	}
	if (data->op_list)
		lst_clear(data->op_list);
}
