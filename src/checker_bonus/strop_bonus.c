/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strop_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 01:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/08 20:09:28 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

t_op	string_to_op(const char *str)
{
	if (!str || !*str)
		return (OP_NULL);
	if (ft_strcmp(str, "pa") == 0)
		return (OP_PA);
	if (ft_strcmp(str, "pb") == 0)
		return (OP_PB);
	if (ft_strcmp(str, "sa") == 0)
		return (OP_SA);
	if (ft_strcmp(str, "sb") == 0)
		return (OP_SB);
	if (ft_strcmp(str, "ss") == 0)
		return (OP_SS);
	if (ft_strcmp(str, "ra") == 0)
		return (OP_RA);
	if (ft_strcmp(str, "rb") == 0)
		return (OP_RB);
	if (ft_strcmp(str, "rr") == 0)
		return (OP_RR);
	if (ft_strcmp(str, "rra") == 0)
		return (OP_RRA);
	if (ft_strcmp(str, "rrb") == 0)
		return (OP_RRB);
	if (ft_strcmp(str, "rrr") == 0)
		return (OP_RRR);
	return (OP_NULL);
}

void	error_read_op(t_ps *data, char *line)
{
	(void)data;
	if (line)
		free(line);
	ft_putendl_fd("Error", 2);
	exit(255);
}
